#include <stddef.h>
#include "base64.h"

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Original decode function generated the table every time. I used the code to
 * print this table and pre-generate it instead.
 */
static const unsigned char dtable[256] = {
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
62, 128, 128, 128, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60,
61, 128, 128, 128, 0, 128, 128, 128, 0, 1, 2, 3, 4, 5,
6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 128, 128, 128, 128, 128, 128, 26, 27,
28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
128, 128, 128
};

/**
 * base64_encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out: output uffer
 * @out_len: length of output buffer
 * Returns: Number of actual bytes encoded into the buffer
 * or 0 on failure
 *
 * Output buffer is nul terminated to make it easier to use as a C string.
 * The nul terminator is * not included in the return length.
 */
size_t base64_encode(const unsigned char *src, size_t len,
                  unsigned char *out, size_t out_len)
{
    unsigned char *pos;
    const unsigned char *end, *in;
    size_t olen;

    olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
    olen += olen / 72; /* line feeds */
    olen++; /* nul termination */
    if (olen < len) {
        return 0; /* integer overflow */
    }
    if (olen > out_len) {
        return 0; /* not enough space in output buffer */
    }
    if (out == NULL) {
        return 0;
    }

    end = src + len;
    in = src;
    pos = out;
    while (end - in >= 3) {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in) {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1) {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        } else {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                          (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    *pos = '\0';
    return pos - out;
}


/**
 * base64_decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Output buffer to decode into
 * @out_len: Length of output buffer
 * Returns: Length of encoded data, or 0 on failure
 */
size_t base64_decode(const unsigned char *src, size_t len,
                  unsigned char *out, size_t out_len)
{
    unsigned char *pos, block[4], tmp;
    size_t i, count, olen;
    int pad = 0;

    count = 0;
    for (i = 0; i < len; i++) {
        if (dtable[src[i]] != 0x80)
            count++;
    }

    if (count == 0 || count % 4)
        return 0;

    olen = count / 4 * 3;
    if (olen > out_len) {
        return 0;
    }
    pos = out;
    if (out == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; i < len; i++) {
        tmp = dtable[src[i]];
        if (tmp == 0x80)
            continue;

        if (src[i] == '=')
            pad++;
        block[count] = tmp;
        count++;
        if (count == 4) {
            *pos++ = (block[0] << 2) | (block[1] >> 4);
            *pos++ = (block[1] << 4) | (block[2] >> 2);
            *pos++ = (block[2] << 6) | block[3];
            count = 0;
            if (pad) {
                if (pad == 1)
                    pos--;
                else if (pad == 2)
                    pos -= 2;
                else {
                    /* Invalid padding */
                    return 0;
                }
                break;
            }
        }
    }

    return pos - out;
}

/* Test main */
#ifdef BASE64_TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int base64Test() {
    uint8_t data_to_encode[] = "123456789";

    printf("Original character string is: %s len:%d\n", data_to_encode, strlen(data_to_encode));

    uint8_t * encoded_buf=(uint8_t*)malloc(sizeof(uint8_t)*128);
    memset(encoded_buf,0, sizeof(uint8_t)*128);

    int encoded_len = base64_encode(data_to_encode, strlen(data_to_encode), encoded_buf, 128);
    printf("Base-64 encoded string is: %s len: %d\n", encoded_buf, encoded_len);

    uint8_t * decoded_buf=(uint8_t*)malloc(sizeof(uint8_t)*128);
    memset(decoded_buf,0, sizeof(uint8_t)*128);

    int decoded_len = base64_decode(encoded_buf, encoded_len, decoded_buf, 128);
    printf("Base-64 decoded string is: %s len: %d\n", decoded_buf, decoded_len);
    return 0;
}

int main(void) {
    return base64Test();
}
#endif