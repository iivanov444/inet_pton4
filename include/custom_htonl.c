/* glibc's htonl - https://codebrowser.dev/glibc/glibc/inet/htonl.c.html */

#include <stdint.h>

#undef htonl

static uint32_t htonl(uint32_t const value) {
	/* GCC 4.6 (and newer) and Clang 8 (and newer) */
	#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
		/* If the system is Little-Endian, swap the bytes */
        	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            		uint8_t *bytePtr;
			bytePtr = (uint8_t *)&value;

            		/* Cast to uint32_t to prevent undefined behavior */
			return ((uint32_t)bytePtr[0] << 24) |
			       ((uint32_t)bytePtr[1] << 16) |
                   	       ((uint32_t)bytePtr[2] << 8)  |
                               bytePtr[3];
		#else
		/* If the system is Big-Endian, return the value as-is */
			return value;
		#endif

	/* Fallback for older or non-conforming compilers */
	#else
		uint32_t testValue;
		testValue = 1;

		if (*(uint8_t *)&testValue == 1) {
			/* If the system is Little-Endian, swap the bytes */
			uint8_t *bytePtr;
			bytePtr = (uint8_t *)&value;

			return ((uint32_t)bytePtr[0] << 24) |
                   	       ((uint32_t)bytePtr[1] << 16) |
                   	       ((uint32_t)bytePtr[2] << 8)  |
                   	       bytePtr[3];
		}
		
		else {
			/* If the system is Big-Endian, return the value as-is */
			return value;
		}
	#endif
}
