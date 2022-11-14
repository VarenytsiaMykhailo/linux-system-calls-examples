#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;
extern char  environ;

int main(int argc, char * argv[], char * envp[]){
    int i;
    for (i=0; envp[i]; i++)
        printf("%s\n", envp[i]);
    exit(0);
}