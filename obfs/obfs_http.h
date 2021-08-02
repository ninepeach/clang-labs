#ifndef OBFS_HTTP_H
#define OBFS_HTTP_H

#include "obfs.h"
#include "../sds/sds.h"

int obfs_http_request(obfs_st *, sds);
	int obfs_http_response(obfs_st *, sds);

#endif
