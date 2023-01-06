#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

extern char **environ; // Глобальное окружение

// envp - копия окружения на момент старта программы
int main(int argc, char *argv[], char *envp[]) {
    int i;

    printf("_____________________Environ before add\n");
    for (i = 0; envp[i]; i++) {
        printf("%s\n", envp[i]);
    }

    putenv("A=AAA");
    putenv("B=BBB");
    putenv("TERM=qwerty");
    putenv("A");

    printf("\n\n_____________________Environ after add with environ\n");
    for (i = 0; environ[i]; ++i) {
        printf("%s\n", environ[i]);
    }


    printf("\n\n_____________________getenv:\n");
    printf("HOME=%s\n", getenv("HOME"));
    printf("A=%s\n", getenv("A"));
    printf("G=%s\n", getenv("G"));

    exit(0);
}