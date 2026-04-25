/* Example usage */

#include <stdio.h>

#include "custom_socket.h" /* for in_addr */
#include "inet_pton4.c"
#include "custom_ntohl.c"

int main(void) {
	struct in_addr ipv4_addr;
	char *ip;

	int exit_code;
	exit_code = 0;
	
	ip = "1.2.3.4";
	exit_code = inet_pton4(ip, &ipv4_addr);
	printf("Network IP: 0x%08X\n", ntohl(ipv4_addr.s_addr));
	printf("Exit code: %d\n", exit_code);
	

	return 0;
}
