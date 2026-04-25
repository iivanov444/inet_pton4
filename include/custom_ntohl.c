/* Credits: https://codereview.stackexchange.com/questions/149717/implementation-of-c-standard-library-function-ntohl */

#include <stdint.h>
#include <string.h>

#undef ntohl

static uint32_t ntohl(uint32_t const value) {
    uint8_t *bytePtr;
    bytePtr = (uint8_t *)&value;

    return ((uint32_t) bytePtr[3] << 0)
         | ((uint32_t) bytePtr[2] << 8)
         | ((uint32_t) bytePtr[1] << 16)
         | ((uint32_t) bytePtr[0] << 24);
}
