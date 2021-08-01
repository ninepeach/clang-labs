#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>

uint64_t crc16(uint64_t crc, const unsigned char *s, uint64_t l);

#ifdef CRC16_TEST
int crc16Test(int argc, char *argv[]);
#endif

#endif
