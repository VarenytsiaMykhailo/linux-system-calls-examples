#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

extern int errno;

// ./cmake-build-debug/b04
// Ошибка если запускать программу из других путей, а не из корня. Решение: в env нельзя задавать относительные пути, нужно задавать абсолютные см программу b05
int main() {
    setenv("PATH", "../../a:../../b:../../c", 1);
    execlp("prog", "prog", NULL); // Программа запустит программу из первого найденного каталога
    perror("exec");

    return 0;
}