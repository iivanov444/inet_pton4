/* inet_pton implementation for IPv4 */

#include "custom_socket.h"
#include "custom_htonl.c"

/* #include <stdio.h> /* For debugging */


/* More information for implementing inet_pton compatible with both ipv4 and ipv6
 * https://github.com/torvalds/linux/blob/master/include/linux/socket.h
 * #define AF_INET  2
 * #define AF_INET6 10
 */

/* Return values:
 * 1  - Success - network address was valid and converted
 * 0  - Failure - src (source) doesn't contain a valid network address
 * -1 - Failure - af (address family) is not valid and errno is set to EAFNOSUPPORT
 * 
 * https://www.man7.org/linux/man-pages/man3/inet_pton.3.html
 */

/* https://stackoverflow.com/questions/67774740/how-to-implement-inet-pton-in-c */


int inet_pton4(const char *src, void *dst) {
	const char *ptr;
	uint32_t addr;
	unsigned int octet1, octet2, octet3, octet4;

	ptr = src;
	addr = 0;
	octet1 = 0; octet2 = 0; octet3 = 0; octet4 = 0;


	/* Octet 1 {{{ */
	while (*ptr >= '0' && *ptr <= '9') {
		unsigned int digit;
		digit = (unsigned int) (*ptr - '0');

		octet1 = octet1 * 10 + digit;
		ptr++;
	}
	if (octet1 > 255 || *ptr != '.') {
		/*printf("Failure at line %d, with octet1 = %d and return code 0\n", __LINE__, octet1); /* Uncomment for debugging */
		return 0;
	}
	addr |= (octet1 << 24);
	ptr++;
	/* }}} */


	/* Octet 2 {{{ */
	while (*ptr >= '0' && *ptr <= '9') {
		unsigned int digit;
		digit = (unsigned int) (*ptr - '0');

		octet2 = octet2 * 10 + digit;
		ptr++;
	}
	if (octet2 > 255 || *ptr != '.') {
		/*printf("Failure at line %d, with octet2 = %d and return code 0\n", __LINE__, octet2); /* Uncomment for debugging */
		return 0;
	}
	addr |= (octet2 << 16);
	ptr++;
	/* }}} */


	/* Octet 3 {{{ */
	while (*ptr >= '0' && *ptr <= '9') {
		unsigned int digit;
		digit = (unsigned int) (*ptr - '0');

		octet3 = octet3 * 10 + digit;
		ptr++;
	}
	if (octet3 > 255 || *ptr != '.') {
		/*printf("Failure at line %d, with octet3 = %d and return code 0\n", __LINE__, octet3); /* Uncomment for debugging */
		return 0;
	}
	addr |= (octet3 << 8);
	ptr++;
	/* }}} */


	/* Octet 4 {{{ */
	while (*ptr >= '0' && *ptr <= '9') {
		unsigned int digit;
		digit = (unsigned int) (*ptr - '0');

		octet4 = octet4 * 10 + digit;
		ptr++;
	}
	if (octet4 > 255 || *ptr != '\0') {
		/*printf("Failure at line %d, with octet4 = %d and return code 0\n", __LINE__, octet4); /* Uncomment for debugging */
		return 0;
	}
	addr |= octet4;
	ptr++;
	/* }}} */

	*(uint32_t*)dst = htonl(addr);

	return 1;
}
