#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "fswrap.h"

#define EXPECT_EQ_STR(l,r) \
    do {  strcmp(l,r) ? printf("* error "#r"\n") : printf("success "#r"\n"); } while (0)

#define EXPECT_EQ_NUM(l,r) \
    do {  (l == r) ? printf("success "#r"\n") : printf("* error"#r"\n"); } while (0)

int expect_eq_str(char* l, char* r) {
    return !strcmp(l, r);
}

void param_test() {
    FsWrap fswp = {0};
    int ret = 0;
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_open_sync(NULL, "w", &fswp));
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_open_sync("./test.txt", "w", NULL));
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_open_sync("./test.txt", NULL, &fswp));
    EXPECT_EQ_NUM(0, fswrap_open_sync("./test.txt", "w", &fswp));
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_write_sync(NULL, 0, 0, &fswp));

    char buf[] = "aa55";
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_write_sync(buf, sizeof(char), sizeof(buf), NULL));
    fswp.fp = NULL;
    EXPECT_EQ_NUM(FSW_PARAM_ERROR, fswrap_write_sync(buf, sizeof(char), sizeof(buf), &fswp));
}

void open_test() {
    FsWrap fswp = {0};
    int ret = 0;

    EXPECT_EQ_NUM(ENOENT, fswrap_open_sync("./open.txt", "r", &fswp));
    EXPECT_EQ_NUM(0, fswrap_open_sync("./a.txt", "w", &fswp));
    EXPECT_EQ_STR("./a.txt", fswp.path);
 }

void write_test() {
   FsWrap fswp = {0};
   int ret = 0;
   EXPECT_EQ_NUM(0, fswrap_open_sync("./write.txt", "w", &fswp));
   
   char buf[] = "aa55";
   EXPECT_EQ_NUM(0, fswrap_write_sync(buf, sizeof(char), sizeof(buf), &fswp));
}

int main() {
    printf("[test begin]\n");
    param_test();
    open_test();
    write_test();
    printf("[test end]\n");
    return 0;
}
