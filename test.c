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
    DirUtil* du = du_init();
    
    if (!du) return 0;
    
    char** list = du->get(path, pattern);

    if (list) {
	unsigned int i = 0;
	while (list[i] != NULL) {
	    printf("[%s]\n", list[i]);
	    i++;
	}
    }
    du->close();
    printf("[test end]\n");
    return 0;
}
