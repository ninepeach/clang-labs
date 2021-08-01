#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "../ae.h"
#include "../anet.h"

#ifndef UNUSED
#define UNUSED(x)   ((void)(x)) /* to avoid warnings */
#endif

int main (int argc, char **argv) {
    char aneterr[ANET_ERR_LEN];
    long long wbuf_len = 0, wbuf_pos = 0;
    char rbuf[1024*16];
    char wbuf[1024*16];
    int inputMod = 1;
    int done = 0;


    int fd = anetTcpConnect(NULL, "127.0.0.1", 3000);

    if (fd==-1) {
        printf("Connection Error\n");
        return 1;
    } else {
    	printf("Connected\n");
    }

    /* Use non blocking I/O. */
    if (anetNonBlock(aneterr,fd) == ANET_ERR) {
        fprintf(stderr, "Can't set the socket in non blocking mode: %s\n",
            aneterr);
        exit(1);
    }

    while(!done) {
        int mask = AE_READABLE;

        if (inputMod) mask |= AE_WRITABLE;
        mask = aeWait(fd, mask, 1000);

        /* Handle the readable state: we can read replies from the server. */
        if (mask & AE_READABLE) {
            ssize_t nread = read(fd, rbuf, sizeof(rbuf));
            if (nread > 0) {
                printf("recv: %s\n", rbuf);
            }
            memset(rbuf, 0, sizeof(rbuf));  
            inputMod = 1;          
        }

        /* Handle the writable state: we can send protocol to the server. */
        if (mask & AE_WRITABLE) {

            printf("Please Input:\n");
            ssize_t nread = read(STDIN_FILENO, wbuf, sizeof(wbuf));

            if (nread == -1) {
                fprintf(stderr, "Error reading from stdin: %s\n",
                            strerror(errno));
                exit(1);
            }

            ssize_t nwritten = write(fd, wbuf, nread);
            printf("Send: %s\n", wbuf);
            inputMod = 0;

            if (nwritten == -1) {
                if (errno != EAGAIN && errno != EINTR) {
                    fprintf(stderr, "Error writing to the server: %s\n",
                        strerror(errno));
                    exit(1);
                }
            }
        }
    }
    return 0;
}