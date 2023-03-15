#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "du.h"

#define EXPECT_EQ_STR(l,r) \
    do {  strcmp(l,r) ? printf("* error "#r"\n") : printf("success "#r"\n"); } while (0)

#define EXPECT_EQ_NUM(l,r) \
    do {  (l == r) ? printf("success "#r"\n") : printf("* error"#r"\n"); } while (0)

int expect_eq_str(char* l, char* r) {
    return !strcmp(l, r);
}


int main() {
    printf("[test begin]\n");
    const char *pattern = "*";
    const char *path = "./";
    DU* du = du_init();
    char** list = du->get_current(path, pattern);
    if (*list) {
	
    }
    printf("[test end]\n");
    return 0;
}
