#ifndef OBFS_H
#define OBFS_H

#include <stdint.h>
#include <stdbool.h>

#define OBFS_OK         0
#define OBFS_ERR       -1
#define OBFS_NEED_MORE -2

typedef struct obfs_st {
    const char *name;
    const char *host;
    const char *uri;
    const char *method;
    uint16_t port;
    int obfs_stage;
    int deobfs_stage;
    char *buf;
} obfs_st;

typedef struct obfs_para_st {
    const char *name;
    const char *host;
    const char *uri;
    const char *method;
    uint16_t port;

    int(*const obfs_request)(obfs_st *, char *, size_t);
    int(*const obfs_response)(obfs_st *, char *, size_t);
    int(*const deobfs_request)(obfs_st *, char *, size_t);
    int(*const deobfs_response)(obfs_st *, char *, size_t);
    void(*const disable)(obfs_st *);
    int(*const is_enable)(obfs_st *);
} obfs_para_st;

#endif
