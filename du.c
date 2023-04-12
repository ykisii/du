#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "du.h"

#define DEFAULT_BUF_SIZE (128)

static DirUtil *du;
static char** du_get_names(const char* path, const char* pattern);
static void du_close_obj(void);

DirUtil* du_init(void) {
  if (!du) {
    du = (DirUtil*)malloc(sizeof(DirUtil));
    du->get = du_get_names;
    du->close = du_close_obj;
    du->buff_size = DEFAULT_BUF_SIZE;
  }
  return du;
}

static unsigned int du_set_name(const char*name, char** list, const int index) {
  if (!name || !list) {
    return -1;
  }
  size_t len = strlen(name);
  char* tmp = (char*)malloc(sizeof(char) * len+1);
  if (!tmp) {
    printf("allocation error\n");
    free(list);
    return -1;
  }
  list[index] = tmp;
  memset(list[index], 0, len+1);
  strncpy(list[index], name, len);
  return index;
}

static
char** du_alloc_buff(const size_t size) {
  if (size <= 0) {
    return NULL;
  } 
  return (char**)malloc(sizeof(char*) * size);
}

static
void du_close_obj(void) {
  if (du) {
    free(du);
    du = NULL;
  }
}

static
char** du_get_names(const char* path, const char* pattern) {
  if (!path || !du) return NULL;
  
  char** names = du_alloc_buff(sizeof(char*) * du->buff_size);
  if (!names) return NULL;

  size_t count = du->buff_size;
  unsigned int i = 0;
  memset(names, 0, (sizeof(char*) * du->buff_size));
  
  DIR *dp = opendir(path);
  if (!dp) return NULL;
  struct dirent *dirent;

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
    if (du_set_name(dirent->d_name, names, i) < 0) {
      return NULL;
    }
    count--;
    i++;
  }
  names[i] = NULL;
  return names;
}
