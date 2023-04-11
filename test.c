#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "du.h"

#define EXPECT_EQ_STR(l,r) \
    do {  strcmp(l,r) ? printf("\t* error "#r"\n") : printf("\tsuccess "#r"\n"); } while (0)

#define EXPECT_EQ_NUM(l,r) \
    do {  (l == r) ? printf("\tsuccess "#r"\n") : printf("\t* error"#r"\n"); } while (0)

int expect_eq_str(char* l, char* r) {
    return !strcmp(l, r);
}

static void t_path_is_null(void) {
  printf("[path is null]\n");
  const char *pattern = "*";
  const char *path = "./ho";
  DirUtil* du = du_init();
    
  if (!du) return;
    
  char** list = du->get(path, pattern);
  EXPECT_EQ_NUM(list, NULL);
  du->close();
}

static void t_print_dir(const char* path) {
  const char *pattern = "*";
  DirUtil* du = du_init();
    
  if (!du) return;
    
  char** list = du->get(path, pattern);

  if (list) {
	  unsigned int i = 0;
	  while (list[i] != NULL) {
	    printf("[%s]\n", list[i]);
	    i++;
	  }
  }
  du->close();
}

int main() {
    printf("[test begin]\n");
    t_print_dir("./");
    t_path_is_null();
    printf("[test end]\n");
    return 0;
}
