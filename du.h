/**
 * listup current directory
 *
 * [in] path: path to directory
 * [in] pattern: filter pattern string(ex: *.c, h?ello.c)
 * return: poinster to array of entry names
 */
typedef char** (*du_getcur)(const char* path, const char* pattern);

/**
 * close terminate du structure
 */
typedef void (*du_close)(void);

typedef struct _du{
    du_getcur get;
    du_close  close;
    size_t    buff_size;
} DirUtil;

/**
 * Initialize Dirent Util Object
 *
 * return: pointer to DirUtil Structure
 */
DirUtil* du_init(void);
