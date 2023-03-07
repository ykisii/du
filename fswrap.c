#include <stdio.h>
#include "fswrap.h"

int fswrap_open_sync(const char* path, const char* mode, FsWrap* wrapper) {
    if (!path || !mode || !wrapper)
	return FSW_PARAM_ERROR;
    return 0;
}

