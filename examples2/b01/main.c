#include <stdio.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

int main() {
    execlp("prog", "prog", NULL); // Ошибка т.к. в переменной PATH окружения нет пути для програмы prog
    perror("exec");

    return 0;
}
