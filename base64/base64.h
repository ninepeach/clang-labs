#ifndef BASE64_H
#define BASE64_H

size_t base64_encode(const unsigned char *src, size_t len,
                  unsigned char *out, size_t out_len);
size_t base64_decode(const unsigned char *src, size_t len,
                  unsigned char *out, size_t out_len);

#endif /* BASE64_H */
