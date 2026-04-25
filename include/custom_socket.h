#ifndef CUSTOM_SOCKET_H
#define CUSTOM_SOCKET_H

#include <stddef.h>
#include <stdint.h>


/* Define sa_family_t here so we avoid including <sys/socket.h> just for it
 * sa_family_t is defined __kernel_sa_family_t in the linux kernel:
 * https://github.com/torvalds/linux/blob/1a5304fecee523060f26e2778d9d8e33c0562df3/include/linux/socket.h#L28
 *
 * and __kernel_sa_family_t is defined unsigned short in the linux kernel:
 * https://github.com/torvalds/linux/blob/1a5304fecee523060f26e2778d9d8e33c0562df3/include/uapi/linux/socket.h#L10
 */
typedef unsigned short sa_family_t;

/* Used for alignment - used from https://man.archlinux.org/man/core/man-pages/sys_socket.h.0p.en */
#define _SS_MAXSIZE 128
#define _SS_ALIGNSIZE (sizeof(int64_t))
/* Definitions used for sockaddr_storage struct */
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(sa_family_t))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(sa_family_t) + \
		      _SS_PAD1SIZE + _SS_ALIGNSIZE))


struct in_addr { /* IPv4 only */
	uint32_t s_addr;
};

struct sockaddr { /* IPv4 only */
	unsigned short sa_family;        /* address family, AF_xxx */
	char	       sa_data[14];      /* 14 bytes of protocol address */
}; /* 16 bytes */
/* A pointer to a struct sockaddr can be cast to a pointer to a struct sockaddr_in and vice-versa */

struct sockaddr_in { /* IPv4 only */
	short int          sin_family;   /* Address family, AF_INET */
	unsigned short int sin_port;     /* Port number - must be set in Network Byte Order (Big Endian) by using htons() */
	struct in_addr     sin_addr;     /* Internet address */
	unsigned char      sin_zero[8];  /* Add 8 byte padding so the struct is the same size as sockaddr.
					  * Use memset() to set it all zeros.
					  */
}; /* 16 bytes */
/* A pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vice-versa
 * Note: Even if connect() expects a struct sockaddr*, a struct sockaddr_in* can be used and cast at the last second
 */


struct in6_addr { /* IPv6 only */
	unsigned char	   s6_addr[16];	  /* IPv6 address */
};
struct sockaddr_in6 { /* IPv6 only */
	uint16_t 	   sin6_family;   /* Address family, AF_INET6 */
	uint16_t 	   sin6_port;     /* Port number - must be set in Network Byte Order (Big Endian) by using htons() */
	uint32_t 	   sin6_flowinfo; /* IPv6 flow information */
	struct in6_addr    sin6_addr;     /* IPv6 address */
	uint32_t 	   sin6_scope_id; /* Scope ID */
};


struct addrinfo {
	int 		   ai_flags;      /* AI_PASSIVE, AI_CANONNAME, etc. */
	int 		   ai_family;     /* AF_INET, AF_INET6, AF_UNSPEC (IP version agnostic) */
	int 		   ai_socktype;   /* SOCK_STREAM, SOCK_DGRAM */
	int 		   ai_protocol;   /* use 0 for "any" */
	size_t 		   ai_addrlen;    /* size of ai_addr in bytes */
	struct sockaddr    *ai_addr;      /* struct sockaddr_in or _in6 */
	char 		   *ai_canonname; /* full canonical hostname */
	
	struct addrinfo    *ai_next;      /* linked list, next node */
};


struct sockaddr_storage {
	sa_family_t        ss_family;     /* address family */

	/* padding - implementation specific */
	char               __ss_pad1[_SS_PAD1SIZE];
	int64_t            __ss_align;
	char               __ss_pad2[_SS_PAD2SIZE];
};


#endif /* CUSTOM_SOCKET_H */
/* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html */
