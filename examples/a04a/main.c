#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

extern char **environ; // Глобальное окружение

// envp - копия окружения на момент старта программы
int main(int argc, char *argv[], char *envp[]) {
    int i;
    putenv("A=AAA");
    putenv("B=BBB");
    putenv("TERM=qwerty");
    printf("\n\n_____________________After add with environ\n");
    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
    printf("\n\n_____________________getenv:\n");
    printf("HOME=%s\n", getenv("HOME"));
    printf("HOME=%s\n", getenv("A"));
    printf("G=%s\n", getenv("G"));

    exit(0);
}