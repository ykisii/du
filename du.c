#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "du.h"

#define DEFAULT_BUF_SIZE (128)

static DirUtil *du;
static char** get(const char* path, const char* pattern);
static void close(void);

DirUtil* du_init(void) {
  if (!du) {
    du = (DirUtil*)malloc(sizeof(DirUtil));
    du->get = get;
    du->close = close;
    du->buff_size = DEFAULT_BUF_SIZE;
  }
  return du;
}

static
void close(void) {
  if (du) {
    free(du);
    du = NULL;
  }
}

static
char** get(const char* path, const char* pattern) {
  if (!path || !du) return NULL;
  DIR *dp = opendir(path);
  struct dirent *dirent;
  char** names = NULL;
  names = (char**)malloc(sizeof(char*) * du->buff_size);
  size_t count = du->buff_size;
  unsigned int i = 0;
  memset(names, 0, (sizeof(char*) * du->buff_size));
  while((dirent = readdir(dp)) != NULL) {
    if (count <= 0) {
      printf("reallocate buffer\n");
      char** tmp = (char**)realloc(names, sizeof(char*) * du->buff_size);
      if (!tmp) {
        free(names);
        return NULL;
      }
      names = tmp;
    }
    size_t len = strlen(dirent->d_name);
    char* tmp = (char*)malloc(sizeof(char) * len+1);
    if (!tmp) {
      printf("allocation error\n");
      free(names);
      return NULL;
    }
    names[i] = tmp;
    memset(names[i], 0, len+1);
    strncpy(names[i], dirent->d_name, len);
    count--;
    i++;
  }
  names[i] = NULL;
  return names;
}
