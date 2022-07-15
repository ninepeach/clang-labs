#ifdef DICT_TEST_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testhelp.h"
#include "sds.h"
#include "dict.h"

#define UNUSED(x) (void)(x)

unsigned int dictSdsHash(const void *key) {
    return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
}

int dictSdsKeyCompare(void *privdata, const void *key1,
        const void *key2)
{
    int l1,l2;
    DICT_NOTUSED(privdata);

    l1 = sdslen((sds)key1);
    l2 = sdslen((sds)key2);
    if (l1 != l2) return 0;
    return memcmp(key1, key2, l1) == 0;
}

void dictSdsDestructor(void *privdata, void *val)
{
    DICT_NOTUSED(privdata);

    sdsfree(val);
}

dictType test1DictType = {
    dictSdsHash,                /* hash function */
    NULL,                       /* key dup */
    NULL,                       /* val dup */
    dictSdsKeyCompare,          /* key compare */
    dictSdsDestructor,          /* key destructor */
    NULL                        /* val destructor */
};

int dictTest(void) {
    {
        sds key1 = sdsnew("key1");
        sds val1 = sdsnew("val1");
        dict *dict1 = dictCreate(&test1DictType, NULL);

        dictEntry *de;
        de = dictFind(dict1, key1);
        if (!de) {
            dictAdd(dict1, key1, val1);
        }
        de = dictFind(dict1, key1);
        sds *o = dictGetVal(de);

        test_cond("dict find key key1=val1",
            sdslen(o) == 4 && memcmp(o,"val1\0",5) == 0)
    }
    test_report()
    return 0;
}

int main(void) {
    return dictTest();
}
#endif
