#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>

extern int errno;

int main() {
    setenv("PATH", "../../b:../../a:../../c", 1);
    execlp("prog", "prog", NULL); // Программа запустит программу из первого найденного каталога
    perror("exec");

    return 0;
}