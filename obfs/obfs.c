#ifdef OBFS_TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obfs.h"
#include "obfs_http.h"

int obfsTest() {
    static obfs_para_st *obfs_para  = NULL;
    struct obfs_st obfs;

    obfs.name = "http";
    obfs.host = "ec0521b170f84bc0.download.microsoft.com";
    obfs.port = 80;

    obfs_http_request(&obfs, sdsnew("czw"));

    obfs.obfs_stage = 0;
    obfs_http_response(&obfs, sdsnew("czw"));
    return 0;
}

int main(void) {
    return obfsTest();
}
#endif