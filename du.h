/**
 * listup current directory
 *
 * [in] path: path to directory
 * [in] pattern: filter pattern string(ex: *.c, h?ello.c)
 * return: poinster to array of entry names
 */
typedef char** (*du_getcur)(const char* path, const char* pattern);

typedef struct _du{
    du_getcur get_current;
    size_t    buff_size;
} DirUtil;

/**
 * init du structure
 * return: pointer to du structure
 */
DirUtil* du_init(void);
/**
 * close terminate du structure
 */
void du_close(void);
