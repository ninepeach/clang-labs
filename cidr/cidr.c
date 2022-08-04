#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

uint32_t cidrInt2Ip(uint32_t ip, char *buf)
{
    sprintf(buf, "%d.%d.%d.%d",
        (ip >> 24) & 0xFF,
        (ip >> 16) & 0xFF,
        (ip >>  8) & 0xFF,
        (ip      ) & 0xFF);

    return 0;
} 

uint32_t cidrIp2Int(const char *ipStr)
{
    uint32_t ipbytes[4]={};
    uint8_t j = 3;

    int i =0;
    while (ipStr+i && i<strlen(ipStr))
    {
        char digit = ipStr[i];
        if (isdigit(digit) == 0 && digit!='.') {
            return 0;
        }
        j=(digit=='.')?j-1:j;
        ipbytes[j]= ipbytes[j]*10 + atoi(&digit);

        i++;
    }

    uint32_t a = (uint32_t)ipbytes[0];
    uint32_t b = (uint32_t)ipbytes[1] << 8;
    uint32_t c = (uint32_t)ipbytes[2] << 16;
    uint32_t d = (uint32_t)ipbytes[3] << 24;

    return a+b+c+d;
}

int cidr2IpRange(const char * cidr, uint32_t *first_ip, uint32_t *final_ip, uint32_t *mask)
{
    uint8_t maskbits;

    int pos=0;
    while (cidr+pos && pos<strlen(cidr)){
        if (*(cidr+pos) == '/'){
            break;
        }
        pos++;
    }

    char *maskstr = strdup(cidr+pos+1);
    char *ipstr = strndup(cidr, pos);

    if (NULL == maskstr)
    {
        return -1; //invalid cidr
    }

    maskbits = atoi(maskstr);
    if (maskbits > 32 || maskbits < 0) {
        free(maskstr);
        free(ipstr);
        return -1; /* Invalid bit count */
    }

    *mask = (0xFFFFFFFFUL << (32 - maskbits)) & 0xFFFFFFFFUL;
    //uint32_t count = (0xFFFFFFFFUL >> maskbits) - 1;
    uint32_t ip = cidrIp2Int(ipstr);

    *first_ip = ip & *mask;
    *final_ip = *first_ip | ~(*mask);

    free(maskstr);
    free(ipstr);
    return 0;
}
