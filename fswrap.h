#pragma once

#include <stdio.h>

#define FSW_BASE		(0xfff0)
#define FSW_PARAM_ERROR		(FSW_BASE - 0x01)

typedef struct FsWrap FsWrap;

struct FsWrap{
    FILE* fp;
    char* path;
    char* mode;
};

/**
 * Open file
 *
 * @param[in]  path:     path to file
 * @param[in]  mode:     file mode
 * @param[out] wrapper:  wrapper object
 */
int fswrap_open_sync(const char* path, const char* mode, FsWrap* wrapper);

/**
 * Write file
 *
 * @param[in]  buf:      path to file
 * @param[in]  size:     size of buf
 * @param[in]  count:    count of write
 * @param[in] wrapper:   wrapper object
 */
int fswrap_write_sync(const void* buf, const size_t size, const size_t count, const FsWrap* wrapper);
