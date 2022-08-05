#ifndef CIDR_H
#define CIDR_H

#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include <sys/types.h>
#include <stdlib.h>

uint32_t cidrInt2Ip(uint32_t ip, char *buf);
uint32_t cidrIp2Int(const char *ipStr);
int cidr2IpRange(const char * cidr, uint32_t *first_ip, uint32_t *final_ip, uint32_t *mask);

#ifdef CIDR_TEST
int cidrTest();
#endif

#endif
