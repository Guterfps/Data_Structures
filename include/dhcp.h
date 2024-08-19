/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 13/2/2023	               */
/* WORKSHEET NAME: DHCP				      */
/* REVIEWER: Matan		                 */
/*--------------------------------------*/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

/*-----------------------------------------------------------------------------
DHCP: The Dynamic Host Configuration Protocol (DHCP) is a network management 
protocol used on Internet Protocol (IP) networks for automatically assigning IP 
addresses and other communication parameters to devices connected to the 
network using a client–server architecture.

main functionalities: DHCPCreate(), DHCPDestroy(), DHCPAllocateIP(), 
					  DHCPFreeIP().
					  
------------------------------------------------------------------------------*/

/* handler for the dhcp */
typedef struct dhcp dhcp_t;

/* return status for DHCPAllocateIP() and DHCPFreeIP() */
typedef enum status
{
    SYS_FAULT = -1,
    SUCCESS = 0,
    INVALID_ADDRESS = 1,
    DOUBLE_FREE = 2,
    OCCUPIED_ADDRESS = 3,
    NO_AVAIL_IP = 4
} status_t;


/*-----------------------------------------------------------------------------
Description: creates a new DHCP.
	
Parameters: net_ip - string representing the ip(ipv4) of the network.
			subnet_mask - 32 bit mask to separate net_ip and host_ip
						 (min value: 2147483648, max value: 4294967292).

Return Value: handler to the new DHCP, or NULL if it fails.

note: if the subnet_mask or net_ip are not valid, the behivior is undefind.

Complexity: 
	time: O(log(n))  
-----------------------------------------------------------------------------*/
dhcp_t *DHCPCreate(const char *net_ip, unsigned int subnet_mask);

/*-----------------------------------------------------------------------------
Description: deletes a DHCP.
	
Parameters: dhcp - handler of dhcp.

Return Value: none.

Complexity: 
	time: O(n) 
-----------------------------------------------------------------------------*/
void DHCPDestroy(dhcp_t *dhcp);

/*-----------------------------------------------------------------------------
Description: allocates an ip address, if the address is not free the next 
			 smallest(bigger than the requested one) address will be allocated.
			 if the requested_ip is NULL the allocated address will be the
			 smallest free address.
	
Parameters: dhcp - handler of dhcp.
			requested_ip - string representing the requested ip(ipv4).
			res_ip - a buffer(needs to be big enough) to store the string 
					 of the allocated address(ipv4).

Return Value: status_t : 
			  SYS_FAULT - memeory error in the system.
			  SUCCESS - if the requested address was allocted.
			  INVALID_ADDRESS - if the requested address is not valid, the 
			  					allocated address is the smallest free address.
			  OCCUPIED_ADDRESS - the requested address is not free, the next 
			  					 smallest(bigger than the requested one) address
			  					 will be allocated.
			  NO_AVAIL_IP - if all addresses bigger than the requested_ip are
			  				not free.
	  
Complexity: 
	time: Avg - O(log(n)), Worst - O(nlog(n)).  
-----------------------------------------------------------------------------*/
status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip, char *res_ip);

/*-----------------------------------------------------------------------------
Description: frees an ip address.
	
Parameters: dhcp - handler of dhcp.
			ip - string representing the ip(ipv4) to free.

Return Value: SUCCESS - the address was freed.
			  INVALID_ADDRESS - the ip address is not valid.
			  DOUBLE_FREE - the ip address is allready free.
			  

Complexity: 
	time: O(log(n))
-----------------------------------------------------------------------------*/
status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip);

/*-----------------------------------------------------------------------------
Description: counts the amount of free ip addresses available.
	
Parameters: dhcp - pointer to a dhcp.

Return Value: the amount of free addresses.

Complexity: 
	time: O(n) 
-----------------------------------------------------------------------------*/
size_t DHCPCountFreeAddresses(const dhcp_t *dhcp);

#endif /* __DHCP_H__ */

