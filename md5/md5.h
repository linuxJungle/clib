#ifndef MD5_H
#define MD5_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define A             0x67452301
#define B             0xefcdab89
#define C             0x98badcfe
#define D             0x10325476
#define A             0x67452301
#define B             0xefcdab89
#define C             0x98badcfe
#define D             0x10325476

/*hash result is 128 bits*/
#define HASH_SIZE     32
/*each group size is 64 bytes */
#define BLOCK_SIZE    64
/*give string len, if len greater 8 bytes, truncation last 8 bytes*/
#define STR_SIZE      8

#define FIRST_PADDING_BYTES 0x80

#define shift(x, n)   (((x) << (n)) | ((x) >> (32 -(n))))
#define F(x, y, z)    (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z)    (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z)    ((x) ^ (y) ^ (z))
#define I(x, y, z)    ((y) ^ ((x) | (~z)))

char* md5_encode (char * str);

#endif /* MD5_H */
