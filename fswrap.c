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

int fswrap_write_sync(const void* buf, const size_t size, const size_t count, const FsWrap* wrapper) {
    if (!buf || !wrapper || !wrapper->fp)
	return FSW_PARAM_ERROR;

    size_t ret = fwrite(buf, size, count, wrapper->fp);
    if (ret != count)
	return errno;

    return 0;
}
