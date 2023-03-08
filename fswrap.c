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
