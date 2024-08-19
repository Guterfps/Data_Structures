/*-------------------------------------------*/
/* DEVELOPER: Itay Guter                    */
/* LAST MODIFIED: 13/2/2023	               */
/* WORKSHEET NAME: DHCP				      */
/* REVIEWER: Matan		                 */
/*--------------------------------------*/

#include <stdio.h>	/* printf() */

#include "dhcp.h"	/* function declaerations and typdefs */

#define SUBNET_MASK 4294967040 /* 11111111111111111111111100000000 */

void Test(void);

int main(void)
{
	Test();
	
	return 0;
}

void Test(void)
{
	const char *net_ip = "123.214.234.128";
	dhcp_t *dhcp = DHCPCreate(net_ip, SUBNET_MASK);
	char ip_res[16] = {'\0'};
	const char *req_ip = "123.214.234.1";
	const char *req_ip2 = "123.214.234.17";
	const char *req_ip3 = "123.214.234.253";
	
	printf("count free ips test:	");
	(256 - 3 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple allocate test:	");
	(SUCCESS == DHCPAllocateIP(dhcp, req_ip, ip_res)) ? 
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	printf("%s\n", ip_res);
	(OCCUPIED_ADDRESS == DHCPAllocateIP(dhcp, req_ip, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("%s\n", ip_res);
	
	printf("simple allocate test2:	");
	(SUCCESS == DHCPAllocateIP(dhcp, req_ip2, ip_res)) ? 
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	printf("%s\n", ip_res);
	(OCCUPIED_ADDRESS == DHCPAllocateIP(dhcp, req_ip2, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("%s\n", ip_res);
	
	printf("simple allocate test3:	");
	(SUCCESS == DHCPAllocateIP(dhcp, req_ip3, ip_res)) ? 
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	printf("%s\n", ip_res);
	(NO_AVAIL_IP == DHCPAllocateIP(dhcp, req_ip3, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("%s\n", ip_res);
	
	printf("random alloc test:	");
	(OCCUPIED_ADDRESS == DHCPAllocateIP(dhcp, NULL, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("%s\n", ip_res);
	
	printf("count free ips test:	");
	(256 - 9 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple free test:	");
	(SUCCESS == DHCPFreeIP(dhcp, req_ip)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("count free ips test:	");
	(256 - 8 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple allocate test:	");
	(SUCCESS == DHCPAllocateIP(dhcp, req_ip, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("%s\n", ip_res);
	
	printf("simple free test:	");
	(SUCCESS == DHCPFreeIP(dhcp, req_ip)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(DOUBLE_FREE == DHCPFreeIP(dhcp, req_ip)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple free test2:	");
	(SUCCESS == DHCPFreeIP(dhcp, req_ip2)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(DOUBLE_FREE == DHCPFreeIP(dhcp, req_ip2)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("simple free test3:	");
	(SUCCESS == DHCPFreeIP(dhcp, req_ip3)) ?
	printf("SUCCESS ✅️, ") : printf("FAIL ❌️, ");
	(DOUBLE_FREE == DHCPFreeIP(dhcp, req_ip3)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("count free ips test:	");
	(256 - 6 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("random alloc test:	");
	(OCCUPIED_ADDRESS == DHCPAllocateIP(dhcp, NULL, ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("%s\n", ip_res);
	
	printf("count free ips test:	");
	(256 - 7 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("invalid address alloc test:	");
	(INVALID_ADDRESS == DHCPAllocateIP(dhcp, "123.214.234.1234", ip_res)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("%s\n", ip_res);
	
	printf("invalid address free test:	");
	(INVALID_ADDRESS == DHCPFreeIP(dhcp, "123.214.234.1234")) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("count free ips test:	");
	(256 - 8 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	while (NO_AVAIL_IP != DHCPAllocateIP(dhcp, NULL, ip_res)) 
	{
		/*printf("%s\n", ip_res);*/
	}
	
	printf("count free ips test:	");
	(0 ==  DHCPCountFreeAddresses(dhcp)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	DHCPDestroy(dhcp);
	dhcp = NULL;
}



