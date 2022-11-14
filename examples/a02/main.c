#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;

int main(int argc, char *argv[], char *envp[]) {
    int i;
    printf("argc=%d\n", argc);
    for (i = 0; i < argc; i++)
        printf("argv[%d]=%s\n", i, argv[i]);
    exit(0);
}
