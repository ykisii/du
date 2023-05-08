#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "du.h"

#define DEFAULT_BUF_SIZE (2)

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

static signed int du_set_name(const char*name, char** list, const int index) {
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
  return (char**)malloc(size);
}

static
char** du_realloc_buff(char** buf, size_t size) {
  if (size <= 0) {
    return NULL;
  }
  char** tmp = (char**)realloc(buf, size);
  if (!tmp) {
    free(buf);
    return NULL; 
  }
  buf = tmp;
  tmp = NULL;
  return buf;
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

  //size_t count = du->buff_size;
  unsigned int i = 0;
  memset(names, 0, (sizeof(char*) * du->buff_size));
  
  DIR *dp = opendir(path);
  if (!dp) return NULL;
  struct dirent *dirent;

  while((dirent = readdir(dp)) != NULL) {
    if ((strncmp(".", dirent->d_name, 1) == 0) || (strncmp("..", dirent->d_name, 2) == 0)) {
      continue;
    }
    if (i >= du->buff_size) {
      size_t realloc_size = du->buff_size + du->buff_size;
      names = du_realloc_buff(names, (sizeof(char*) * realloc_size));
      printf(" reallosize[%ld] names[%p] i[%d]\n ", realloc_size, names, i);
      if (!names) return NULL;
      du->buff_size = realloc_size;
      //count = du->buff_size;
    }
    if (du_set_name(dirent->d_name, names, i) < 0) {
      return NULL;
    }
    i++;
  }
  names[i] = NULL;
  return names;
}
