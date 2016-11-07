#include <stdio.h>
#include "base64.h"

unsigned char *
encode_base64 (const char *data)
{
    int              moder;
    size_t           i;
    size_t           num;
    size_t           len;
    unsigned char   *result, *result_start_ptr;

    len = strlen (data);
    if (len <= 0)
        return NULL;

    moder = len % 3;
    num = (len - moder) / 3;
    if (moder != 0)
        result_start_ptr = result = (unsigned char *)malloc ((num + 1) * 4 + 1);
    else
        result_start_ptr = result = (unsigned char *)malloc (num * 4 + 1);

    for (i = 0; i < num; i++) {
        *result++ = encoder[(data[0] >> 2) & 0x3f];
        *result++ = encoder[(((data[0] & 0x03) << 4) | (data[1] >> 4)) & 0x3f]; 
        *result++ = encoder[((data[1] & 0x0f) << 2 | (data[2] >> 6)) & 0x3f];
        *result++ = encoder[data[2] & 0x3f];

        data += 3;
    }

    switch (moder) {

    case 0:
        break;
    case 1:
        *result++ = encoder[(data[0] >> 2) & 0x3f];
        *result++ = encoder[((data[0] & 0x03) << 4) & 0x3f];
        *result++ = '=';
        *result++ = '=';
        break;
    case 2:
        *result++ = encoder[(data[0] >> 2) & 0x3f];
        *result++ = encoder[(((data[0] & 0x03) << 4) | (data[1] >> 4)) & 0x3f]; 
        *result++ = encoder[((data[1] & 0x0f) << 2) & 0x3f];
        *result++ = '=';
        break;
    default:
        fprintf(stderr, "unknown error.\n");
        return NULL;
    }

    *result = '\0';
    return result_start_ptr;
}

size_t
trim_end_char (const char *data, char bad_char)
{
    size_t  len;

    len = strlen (data);
    if (len <= 0)
        return 0;

    while (*(data+len-1) == bad_char) {
        len--;
    }
    return len;
}

char* 
decode_base64 (const char *data)
{
    size_t      i;
    size_t      len;
    size_t      num;
    size_t      pad_len;
    size_t      encode_len;
    char       *result, *result_start_ptr;

    len = strlen (data);
    if (len <= 0)
        return NULL;

    num = len / 4;
    pad_len = len - trim_end_char (data, '=');
    switch (pad_len) {

    case 0:
        encode_len = 0;
        break;
    case 1:
        encode_len = 2; /*pad 1 bytes =*/
        num--;
        break;
    case 2:
        encode_len = 1; /*pad 2 bytes =*/
        num--;
        break;
    default:
        return NULL;
    }
    encode_len += num * 3;
    result_start_ptr = result = (char *)malloc (encode_len);

    for (i = 0; i < num; i++) {
        *result++ = ((decoder[data[0]] << 2) | (decoder[data[1]] >> 4)) & 0xff; 
        *result++ = ((((decoder[data[1]]) & 0x0f) << 4) | 
                    ((decoder[data[2]] & 0x3c) >> 2)) & 0xff;
        *result++ = ((decoder[data[2]] & 0x03) << 6) | decoder[data[3]]; 
        data += 4;
    }

    switch (pad_len) {
    
    case 0:
        break;
    case 1:
        *result++ = ((decoder[data[0]] << 2) | (decoder[data[1]] >> 4)) & 0xff; 
        *result++ = ((((decoder[data[1]]) & 0x0f) << 4) | 
                    ((decoder[data[2]] & 0x3c) >> 2)) & 0xff;
        break;
    case 2:
        *result++ = ((decoder[data[0]] << 2) | (decoder[data[1]] >> 4)) & 0xff; 
        break;
    default:
        return NULL;
    }

    *result = '\0';

    return result_start_ptr;
}
