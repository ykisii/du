#include <stdio.h>
#include <errno.h>
#include "fswrap.h"

int fswrap_open_sync(const char* path, const char* mode, FsWrap* wrapper) {
    if (!path || !mode || !wrapper)
	return FSW_PARAM_ERROR;

    wrapper->fp = fopen(path, mode);

    if (wrapper->fp == NULL) {
	return errno;
    }
    wrapper->path = (char*)path;
    wrapper->mode = (char*)mode;
    
    return 0;
}

int fswrap_write_sync(void* buf, const size_t buf_size, const FsWrap* wrapper) {
    if (!buf || !wrapper || !wrapper->fp)
	return FSW_PARAM_ERROR;

    printf("buf_size[%ld]\n", buf_size);
    /* for (int i = 0; i < buf_size; i++) { */
    /* 	size_t ret = 0; */
    /* 	size_t count = 1; */

    /* 	ret = fwrite(buf[i], sizeof(char), count, wrapper->fp); */
    /* 	if (ret != count) */
    /* 	    return errno; */
    /* } */
    return 0;
}
