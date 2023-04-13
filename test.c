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

static void t_path_is_invalid(void) {
  printf("[%s]\n", __func__);
  const char *pattern = "*";
  const char *path = "./jfalsjh";
  DirUtil* du = du_init();
    
  if (!du) return;
    
  char** list = du->get(path, pattern);
  EXPECT_EQ_NUM(NULL, list);
  du->close();
}

static void t_path_is_null(void) {
  printf("[%s]\n", __func__);
  const char *pattern = "*";
  const char *path = NULL;
  DirUtil* du = du_init();
    
  if (!du) return;
    
  char** list = du->get(path, pattern);
  EXPECT_EQ_NUM(list, NULL);
  du->close();
}

static void t_print_dir(const char* path) {
  printf("[%s]\n", __func__);
  const char *pattern = "*";
  DirUtil* du = du_init();
    
  if (!du) return;
    
  char** list = du->get(path, pattern);

  if (list) {
	  unsigned int i = 0;
	  while (list[i] != NULL) {
	    printf("\t[%d:%s]\n",i, list[i]);
	    i++;
	  }
  }
  du->close();
}

int main() {
    printf("[test begin]\n");
    t_print_dir("./");
    t_path_is_null();
    t_path_is_invalid();
    printf("[test end]\n");
    return 0;
}
