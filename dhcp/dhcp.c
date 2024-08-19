/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 13/2/2023	               */
/* WORKSHEET NAME: DHCP				      */
/* REVIEWER: Matan		                 */
/*--------------------------------------*/

#include <assert.h>	/* assert() */
#include <stdlib.h>	/* malloc() */
#include <arpa/inet.h>	/* inet_pton() */
#include <string.h>	/* strcpy() */

#include "dhcp.h"	/* function declaerations and typdefs */

#define MAX_MASK ((unsigned int)~3) /* 11111111111111111111111111111100 */ 
#define MIN_MASK ((unsigned int)1 << 31) /* 10000000000000000000000000000000 */


typedef struct node node_t;

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

enum 
{
	ZERO = 0,
	ONE,
	NUM_OF_CHILDREN
};

struct node
{
	node_t *children[NUM_OF_CHILDREN];
	bool_t is_full;
};

struct dhcp
{
	node_t *root;
	unsigned int subnet_mask;
	const char *net_ip;
	size_t depth;
};

static int InitDHCP(dhcp_t *new_dhcp, const char *net_ip, 
								unsigned int subnet_mask);
static void DestroyTrie(node_t *root);
static void InitNode(node_t *new_node);
static size_t CountSetBits(unsigned int n);
static int CreatePath(dhcp_t *dhcp, unsigned int ip);
static size_t CountAllocatedIPs(node_t *node);
static status_t SpecialCaseStatus(status_t invalid_add, bool_t req_add);

static int IsFromNetwork(dhcp_t *dhcp, const char *requested_ip);
static int InAddressRange(unsigned int net_ip, unsigned int ip, 
									unsigned int subnet_mask);


dhcp_t *DHCPCreate(const char *net_ip, unsigned int subnet_mask)
{
	dhcp_t *new_dhcp = NULL;
	#ifndef NDEBUG
		unsigned int assert_ip = 0;
	#endif
	
	assert(NULL != net_ip);
	assert(MIN_MASK < subnet_mask);
	assert(MAX_MASK > subnet_mask);
	assert(1 == inet_pton(AF_INET, net_ip, &assert_ip));
	
	new_dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == new_dhcp)
	{
		return NULL;
	}
	
	if (SYS_FAULT == InitDHCP(new_dhcp, net_ip, subnet_mask))
	{
		DHCPDestroy(new_dhcp);
		new_dhcp = NULL;
		return NULL;
	}
	
	return 	new_dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	DestroyTrie(dhcp->root);
	
	free(dhcp);
	dhcp = NULL;	
}

status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip, char *res_ip)
{
	status_t status = SUCCESS;
	status_t invalid_status = SUCCESS;
	unsigned int ip = 0;
	unsigned int temp_ip = 0;
	char *res = NULL;
	struct in_addr s_ip = {0};
	unsigned int net_ip = 0;
	bool_t req_add = TRUE;
	
	assert(NULL != dhcp);
	assert(NULL != res_ip);
	
	inet_pton(AF_INET, dhcp->net_ip, &net_ip);
	net_ip = htonl(net_ip);
	
	if (NULL == requested_ip)
	{
		ip = net_ip & dhcp->subnet_mask;
	}
	else if (1 != inet_pton(AF_INET, requested_ip, &ip) ||
			 !IsFromNetwork(dhcp, requested_ip))
	{
		invalid_status = INVALID_ADDRESS;
		ip = net_ip & dhcp->subnet_mask;
	}
	else
	{
		ip = htonl(ip);
	}
	
	net_ip &= dhcp->subnet_mask;
	temp_ip = ip;
	
	while (InAddressRange(net_ip, temp_ip, dhcp->subnet_mask) &&
			(OCCUPIED_ADDRESS == (status = CreatePath(dhcp, temp_ip))))
	{
		++temp_ip;
	}
	
	req_add = (temp_ip == ip);
	
	if (SYS_FAULT != status)
	{
		status = SpecialCaseStatus(invalid_status, req_add);
	}
	
	if (!InAddressRange(net_ip, temp_ip, dhcp->subnet_mask))
	{
		status = NO_AVAIL_IP;
	}
	s_ip.s_addr = ntohl(temp_ip);
	res = inet_ntoa(s_ip);
	strcpy(res_ip, res);
	
	return status;
}

status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip)
{
	status_t status = DOUBLE_FREE;
	unsigned int num_ip = 0;
	unsigned int mask = 1;
	int i  = 0;
	node_t *runner = NULL;
	
	assert(NULL != dhcp);
	assert(NULL != ip);
	
	if (1 != inet_pton(AF_INET, ip, &num_ip) ||
		!IsFromNetwork(dhcp, ip))
	{
		return INVALID_ADDRESS;
	}
	
	num_ip = htonl(num_ip);
	runner = dhcp->root;
	mask <<= (dhcp->depth - 1);
	
	for (i = dhcp->depth - 1; 0 <= i; --i, mask >>= 1)
	{
		unsigned int child = (mask & num_ip) >> i;
		
		if (NULL == runner->children[child])
		{
			return INVALID_ADDRESS;
		}
		
		runner->is_full = FALSE;
		runner = runner->children[child];
	}
	
	if (runner->is_full)
	{
		runner->is_full = FALSE;
		status = SUCCESS;
	}
	
	return status;
}

size_t DHCPCountFreeAddresses(const dhcp_t *dhcp)
{
	size_t counter = 0;
	
	assert(NULL != dhcp);
	
	counter = 1 << dhcp->depth;
	counter -= CountAllocatedIPs(dhcp->root);
	
	return counter;
}

static int InitDHCP(dhcp_t *new_dhcp, const char *net_ip, 
								unsigned int subnet_mask)
{
	int status = SUCCESS;
	unsigned int net_add = 0;
	unsigned int broad_add = ~subnet_mask;
	unsigned int serv_add = ~subnet_mask - 1;
	
	assert(NULL != new_dhcp);
	assert(NULL != net_ip);
	assert(MIN_MASK < subnet_mask);
	assert(MAX_MASK > subnet_mask);
	
	new_dhcp->root = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_dhcp->root)
	{
		return SYS_FAULT;
	}
	InitNode(new_dhcp->root);
	
	new_dhcp->net_ip = net_ip;
	new_dhcp->subnet_mask = subnet_mask;
	new_dhcp->depth = CountSetBits(~subnet_mask);
	
	if ((SUCCESS != CreatePath(new_dhcp, net_add)) ||
		(SUCCESS != CreatePath(new_dhcp, broad_add)) ||
		(SUCCESS != CreatePath(new_dhcp, serv_add)))
	{
		status = SYS_FAULT;
	}
	
	return status;
}

static void InitNode(node_t *new_node)
{
	new_node->children[ZERO] = new_node->children[ONE] = NULL;
	new_node->is_full = FALSE;
}

static void DestroyTrie(node_t *root)
{
	if (NULL != root)
	{
		DestroyTrie(root->children[ZERO]);
		DestroyTrie(root->children[ONE]);
		
		free(root);
		root = NULL;
	}
}

static size_t CountSetBits(unsigned int n)
{
	size_t counter = 0;
	
	while (0 < n)
	{
		n &= (n - 1);
		++counter;
	}
	
	return counter;
}

static int CreatePath(dhcp_t *dhcp, unsigned int ip)
{
	unsigned int mask = 1;
	int i  = 0;
	int status = SUCCESS;
	node_t *runner = NULL;
	
	assert(NULL != dhcp);
	
	runner = dhcp->root;
	mask <<= (dhcp->depth - 1);
	
	for (i = dhcp->depth - 1; 0 <= i; --i, mask >>= 1)
	{
		unsigned int child = (mask & ip) >> i;
		
		if (NULL == runner->children[child])
		{
			runner->children[child] = (node_t *)malloc(sizeof(node_t));
			if (NULL == runner->children[child])
			{
				return SYS_FAULT;
			}
			InitNode(runner->children[child]);
		}
		else if (NULL != runner->children[child ^ 1] &&
				runner->children[ZERO]->is_full &&
				runner->children[ONE]->is_full)
		{
			runner->is_full = TRUE;
			return OCCUPIED_ADDRESS;
		}
		runner = runner->children[child];
	}
	
	if (TRUE == runner->is_full)
	{
		status = OCCUPIED_ADDRESS;
	}
	runner->is_full = TRUE;
	
	return status;
}

static size_t CountAllocatedIPs(node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	if (NULL == node->children[ZERO] && 
		NULL == node->children[ONE])
	{
		return node->is_full;
	}
	
	return (CountAllocatedIPs(node->children[ZERO]) + 
			CountAllocatedIPs(node->children[ONE]));
}

static status_t SpecialCaseStatus(status_t invalid_add, bool_t req_add)
{
	status_t status = SUCCESS;
	
	if (INVALID_ADDRESS == invalid_add)
	{
		status = invalid_add;
	}
	else if (FALSE == req_add)
	{
		status = OCCUPIED_ADDRESS;
	}
	
	return status;
}


static int IsFromNetwork(dhcp_t *dhcp, const char *requested_ip)
{
	unsigned int net_ip = 0;
	unsigned int req_ip = 0;
	
	assert(NULL != dhcp);
	
	if (1 == inet_pton(AF_INET, requested_ip, &req_ip) &&
		1 == inet_pton(AF_INET, dhcp->net_ip, &net_ip))
	{
		net_ip = htonl(net_ip);
		req_ip = htonl(req_ip);
		net_ip &= dhcp->subnet_mask;
		req_ip &= dhcp->subnet_mask;
	}
	
	return (net_ip == req_ip);	
}

static int InAddressRange(unsigned int net_ip, unsigned int ip, 
									unsigned int subnet_mask)
{
	return (net_ip == (ip & subnet_mask));
}

