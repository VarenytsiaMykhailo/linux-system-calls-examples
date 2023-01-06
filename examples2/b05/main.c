#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

// cmake-build-debug/b05
// OK
int main() {
    setenv("PATH", "/home/mike/Рабочий стол/AOC/examples2/b:/home/mike/Рабочий стол/AOC/examples2/a:/home/mike/Рабочий стол/AOC/examples2/c:", 1);
    execlp("prog", "prog", NULL); // Программа запустит программу из первого найденного каталога
    perror("exec");

    return 0;
}