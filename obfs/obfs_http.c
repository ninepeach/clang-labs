#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <ctype.h> /* isblank() */

#include "obfs_http.h"
#include "../base64/base64.h"
#include "../sds/sds.h"


static const char *http_request_template =
    "%s %s HTTP/1.1\r\n"
    "Host: %s\r\n"
    "User-Agent: curl/7.%d.%d\r\n"
    "Upgrade: websocket\r\n"
    "Connection: Upgrade\r\n"
    "Sec-WebSocket-Key: %s\r\n"
    "Content-Length: %lu\r\n"
    "\r\n";

static const char *http_response_template =
    "HTTP/1.1 101 Switching Protocols\r\n"
    "Server: nginx/1.%d.%d\r\n"
    "Date: %s\r\n"
    "Upgrade: websocket\r\n"
    "Connection: Upgrade\r\n"
    "Sec-WebSocket-Accept: %s\r\n"
    "\r\n";


int rand_bytes(void *output, int len)
{
    int i;
    int *array = (int *)output;
    for (i = 0; i < len / sizeof(int); i++)
        array[i] = rand();
    // always return success
    return 0;
}

int obfs_http_request(obfs_st *obfs, sds buf)
{
    static int major_version = 0;
    static int minor_version = 0;
    char host_port[256];
    sds http_header;
    char b64[64];
    uint8_t key[16];

    if (obfs == NULL || obfs->obfs_stage != 0) return 0;
    obfs->obfs_stage++;

    major_version = major_version ? major_version : rand() % 51;
    minor_version = minor_version ? minor_version : rand() % 2;


    if (obfs->port != 80)
        snprintf(host_port, sizeof(host_port), "%s:%d", obfs->host, obfs->port);
    else
        snprintf(host_port, sizeof(host_port), "%s", obfs->host);

    if (obfs->method == NULL) obfs->method = "GET";
    if (obfs->uri == NULL) obfs->uri = "/";

    rand_bytes(key, 16);
    base64_encode(key, 16, b64, 64);  

    http_header = sdscatprintf(sdsnew(""), http_request_template, obfs->method,
                 obfs->uri, host_port, major_version, minor_version, b64, sdslen(buf));


    //insert http_header to the head of buf
    int http_header_len = sdslen(http_header);
    int buf_len = sdslen(buf);

    buf = sdsMakeRoomFor(buf, http_header_len);
    sdssetlen(buf, http_header_len+buf_len);

    memmove(buf+http_header_len, buf, buf_len);
    memcpy(buf, http_header, http_header_len);
    buf[http_header_len+buf_len] = '\0';

    sdsfree(http_header);

    printf("%s\n",buf);
    return 0;
}

int obfs_http_response(obfs_st *obfs, sds buf) {
    static int major_version = 0;
    static int minor_version = 0;
    sds http_header;
    char datetime[64];
    uint8_t key[16];
    char b64[64];

    time_t now;
    struct tm *tm_now;

    if (obfs == NULL || obfs->obfs_stage != 0) return 0;
    obfs->obfs_stage++;

    major_version = major_version ? major_version : rand() % 11;
    minor_version = minor_version ? minor_version : rand() % 12;

    time(&now);
    tm_now = localtime(&now);
    strftime(datetime, 64, "%a, %d %b %Y %H:%M:%S GMT", tm_now);

    rand_bytes(key, 16);
    base64_encode(key, 16, b64, 64); 

    http_header = sdscatprintf(sdsnew(""), http_response_template,
                 major_version, minor_version, datetime, b64);


    //insert http_header to the head of buf
    int http_header_len = sdslen(http_header);
    int buf_len = sdslen(buf);

    buf = sdsMakeRoomFor(buf, http_header_len);
    sdssetlen(buf, http_header_len+buf_len);

    memmove(buf+http_header_len, buf, buf_len);
    memcpy(buf, http_header, http_header_len);
    buf[http_header_len+buf_len] = '\0';

    sdsfree(http_header);

    printf("%s\n",buf);
    return 0;
}