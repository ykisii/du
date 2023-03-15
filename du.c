#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "du.h"

#define DEFAULT_BUF_SIZE (128)
static DirUtil *du;
static char** get_current(const char* path, const char* pattern);

DirUtil* du_init(void) {
    if (!du) {
	du = (DirUtil*)malloc(sizeof(DirUtil));
	du->get_current = get_current;
	du->buff_size = DEFAULT_BUF_SIZE;
    }
    return du;
}

void du_close(void) {
    if (du) {
	free(du);
	du = NULL;
    }
}

static
char** get_current(const char* path, const char* pattern) {
    if (!path || !du) return NULL;
    
    DIR *dp = opendir(path);
    struct dirent *dirent;
    char** names;
    names = (char**)malloc(sizeof(char*) * du->buff_size);
    size_t count = du->buff_size;

    
    while((dirent = readdir(dp)) != NULL) {
	if (count <= 0) {
	    printf("reallocate buffer\n");
	}
	size_t len = strlen(dirent->d_name);
	char* tmp = (char*)malloc(sizeof(char) * len+1);
	if (!tmp) {
	    printf("allocation error\n");
	    return NULL;
	}
	*names = tmp;
	memset(*names, 0, len+1);
	strncpy(*names, dirent->d_name, len);
	printf("[%s]\n", *names);
	count--;
    }
    return NULL;
}
