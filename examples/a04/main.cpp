#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

extern int errno;

extern char **environ; // Глобальное окружение

// envp - копия окружения на момент старта программы
int main(int argc, char *argv[], char *envp[]) {
    int i;
    printf("_____________________Before add\n");
    for (i = 0; envp[i]; i++)
        printf("%s\n", envp[i]);
    putenv("A=AAA");
    putenv("B=BBB");
    printf("\n\n_____________________After add\n");
    for (i = 0; envp[i]; i++)
        printf("%s\n", envp[i]);
    printf("\n\n_____________________After add with environ\n");
    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
    exit(0);
}