#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "../ae.h"

int print(struct aeEventLoop *loop, long long id, void *clientData)
{
    printf("%lld - Hello, World\n", id);
    return -1;
}

int main(void)
{
    aeEventLoop *loop = aeCreateEventLoop(0);
    int i;
    for (i = 0; i < 10; i ++) {
        aeCreateTimeEvent(loop, i*1000, print, NULL, NULL);
    }
    aeMain(loop);
    aeDeleteEventLoop(loop);
    return 0;
}
