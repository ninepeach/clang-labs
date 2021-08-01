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


void writeToClient(aeEventLoop *el, int fd, void *clientdata, int mask)
{
    char *buffer = clientdata;
    printf("recv client [%d] data: %s\n", fd, buffer);
    write(fd, buffer, strlen(buffer));
    free(buffer);
    aeDeleteFileEvent(el, fd, mask);
}

void readFromClient(aeEventLoop *el, int fd, void *clientdata, int mask)
{
    int buffer_size = 1024;
    char *buffer = malloc(sizeof(char)*buffer_size);
    memset(buffer, 0,sizeof(char)*buffer_size);

    int size;
    size = read(fd, buffer, buffer_size);
    
    if (size <= 0)
    {
      printf("Client disconnected\n");
      free(buffer);
      aeDeleteFileEvent(el, fd, AE_READABLE);
      return; 
    }
    aeCreateFileEvent(el, fd, AE_WRITABLE, writeToClient, buffer);
}

void acceptTcpHandler(aeEventLoop *el, int fd, void *clientdata, int mask) {
    char neterr[ANET_ERR_LEN];
    int cport, cfd, max = 3;
    char cip[46];
    UNUSED(el);
    UNUSED(mask);
    UNUSED(clientdata);

    while(max--) {
        cfd = anetTcpAccept(neterr, fd, cip, sizeof(cip), &cport);
        if (cfd == ANET_ERR) {
            if (errno != EWOULDBLOCK)
                printf("Accepting client connection: %s\n", neterr);
            return;
        }
        printf("Accepted %s:%d\n", cip, cport);
        // set client socket non-block
        anetNonBlock(NULL, cfd);

        // regist on message callback
        aeCreateFileEvent(el, cfd, AE_READABLE, readFromClient, NULL);
    }
}

int main(int argc, char **argv) {

    aeEventLoop *el;
    char neterr[ANET_ERR_LEN];
    int port = 3000;

    printf("oO0OoO0OoO0Oo Server is starting on port %d oO0OoO0OoO0Oo\n", port);
    int fd = anetTcpServer(neterr, port, "0.0.0.0", 0);
    if (fd == ANET_ERR) {
        printf("create tcp server error: %d\n", ANET_ERR);
        exit(1);
    }

    anetNonBlock(NULL, fd);

    el = aeCreateEventLoop(1024);
    if (el == NULL) {
        printf("create event loop failed\n");
        return 1;
    }

    if (aeCreateFileEvent(el, fd, AE_READABLE, acceptTcpHandler, NULL) == AE_ERR) {
        printf("create event loop failed\n");
        return 1;
    }

    aeMain(el);
    aeDeleteEventLoop(el);
    return 0;
}
