#include "md5.h"
/***
 *    Author:    firebroo
 *    Email:     bianliqiang12@gmail.com
 ***/

static unsigned int       stage1;
static unsigned int       stage2;
static unsigned int       stage3;
static unsigned int       stage4;
static size_t             paded_len;
static const unsigned int k[] =
{
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf,
    0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
    0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
    0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6,
    0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122,
    0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039,
    0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97,
    0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d,
    0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};
static const unsigned int s[] =
{
    7,  12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4,  11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6,  10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static char *__pad_str__ (char *str);
static void __main_loop__ (unsigned int M[]);
static void __die__ (char *str);

void __die__ (char *str)
{
    fprintf(stdout, "%s\n", str);
    exit(-1);
}

char *
__pad_str__ (char *str)
{
    size_t  i;
    size_t  pad_len;
    size_t  str_len;
    char   *result;

    str_len = strlen(str);
    if (str_len <= 0)
        __die__ ("string len is less than or equal 0.");

    pad_len = (str_len % BLOCK_SIZE) > BLOCK_SIZE - STR_SIZE?
              BLOCK_SIZE + (BLOCK_SIZE - STR_SIZE) - (str_len % BLOCK_SIZE):
              (BLOCK_SIZE - STR_SIZE) - (str_len % BLOCK_SIZE);
    paded_len = str_len + pad_len + STR_SIZE;
    result = (char *)malloc (paded_len);
    strcpy(result, str);

    /*first padding an 1 and some 0 until*/
    result[str_len] = FIRST_PADDING_BYTES;
    for (i = 1; i < pad_len; i++) {
        result[str_len + i] = '\0';
    }
    /*padding string len*/
    *(size_t *)(result + str_len - 1 + i + 1) = str_len * 8; /*bit len*/

    return result;
}

/*
 * loop shift
 * FF(a ,b ,c ,d ,Mj ,s ,ti ) =>  a = b + ( (a + F(b,c,d) + Mj + ti) << s)
 * FF(a ,b ,c ,d ,M0 ,7 ,0xd76aa478 )
 * FF(d ,a ,b ,c ,M1 ,12 ,0xe8c7b756 )
 * FF(c ,d ,a ,b ,M2 ,17 ,0x242070db )
 * FF(b ,c ,d ,a ,M3 ,22 ,0xc1bdceee )
 * FF(a ,b ,c ,d ,M4 ,7 ,0xf57c0faf )
 */

void
__main_loop__ (unsigned int M[])
{
    unsigned int f, g;
    unsigned int i, tmp;

    unsigned int a = stage1;
    unsigned int b = stage2;
    unsigned int c = stage3;
    unsigned int d = stage4;
    for (i = 0; i < 64; i++)
    {
        if ( i < 16) {
            f = F (b, c, d);
            g = i;
        } else if (i < 32) {
            f = G (b, c, d);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H (b, c, d);
            g = (3 * i + 5) % 16;
        } else {
            f = I (b, c, d);
            g = (7 * i) % 16;
        }
        a = b + shift ((a + f + k[i] + M[g]), s[i]);

        /*loop shift opt*/
        tmp = d;
        d = c;
        c = b;
        b = a;
        a = tmp;
    }

    stage1 = a + stage1;
    stage2 = b + stage2;
    stage3 = c + stage3;
    stage4 = d + stage4;
}

char *
md5_encode (char * str)
{
    char          *hash;
    char           buf[3];
    unsigned int   i, j;
    unsigned int  *ret;

    stage1 = A;    /*init vector*/
    stage2 = B;
    stage3 = C;
    stage4 = D;

    ret = (unsigned int *) __pad_str__(str);
    for (i = 0; i < paded_len / BLOCK_SIZE; i++) {
        unsigned int num[BLOCK_SIZE / 4];
        for (j = 0; j < BLOCK_SIZE / 4; j++)  /*64 bytes equal 16's int*/
            num[j] = ret[i * (BLOCK_SIZE / 4) + j];
        __main_loop__ (num);
    }
    free (ret);

    hash = (char *)malloc (HASH_SIZE + 1);
    for (i = 0; i < 4; i++) {
        sprintf (buf, "%02x",((unsigned char *)&stage1)[i]);
        memcpy (hash + i * 2, buf, 2);
        sprintf (buf, "%02x",((unsigned char *)&stage2)[i]);
        memcpy (hash + 8 + i * 2, buf, 2);
        sprintf (buf, "%02x",((unsigned char *)&stage3)[i]);
        memcpy (hash + 16 + i * 2, buf, 2);
        sprintf (buf, "%02x",((unsigned char *)&stage4)[i]);
        memcpy (hash + 24 + i * 2, buf, 2);
    }

    for (i = 0; i < HASH_SIZE; i++) {
        hash[i] = toupper (hash[i]);
    }

    hash[HASH_SIZE] = '\0';
    return hash;
}

/*
int
main (void)
{
    char *ret = md5_encode("admin");
    printf("%s\n", ret);
    free (ret);
    return 0;
}
*/
