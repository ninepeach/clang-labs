#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Test main */
#ifdef CIDR_TEST_MAIN

#include "cidr.h"

int cidrTest() {

    uint32_t first_ip, final_ip;
    uint32_t mask;
    uint32_t count;

    char ipStr[16];
    char maskStr[16];
    char ip1Str[16];
    char ip2Str[16];

    printf("cidrIp2Int: 3232235521 == %u\n", cidrIp2Int("192.168.0.1"));
    printf("cidrIp2Int: 3232235522 == %u\n", cidrIp2Int("192.168.0.2"));
   
    cidrInt2Ip(3232235521, &ip1Str);
    cidrInt2Ip(3232235522, &ip2Str);

    printf("cidrInt2Ip: 192.168.0.1 == %s\n", ip1Str);
    printf("cidrInt2Ip: 192.168.0.2 == %s\n", ip2Str);


    if (cidr2IpRange("192.168.0.1/28", &first_ip, &final_ip, &mask) < 0) {
        return -1; // invalid cidr string
    }

    cidrInt2Ip(first_ip, &ip1Str);
    cidrInt2Ip(final_ip, &ip2Str);
    cidrInt2Ip(mask, &maskStr);

    printf("cidr2IpRange: %s-%s mask:%s\n", ip1Str, ip2Str, maskStr);

    int current_ip = first_ip;
    while (current_ip<=final_ip) {
        cidrInt2Ip(current_ip, &ipStr);
        cidrInt2Ip(mask, &maskStr);
        printf("%s(%u) %s(%u)\n", ipStr, current_ip, maskStr, mask);
        current_ip++;
    }

    return 0;
}

int main(void) {
    return cidrTest();
}
#endif