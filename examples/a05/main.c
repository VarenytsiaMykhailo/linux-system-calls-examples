#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

extern int errno;

int main(int argc, char *argv[]) {
    int l, p;
    char *ptr;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file filemode\n", argv[0]);
        exit(1);
    }
    p = strtol(argv[2], &ptr, 8);
    if (strlen(argv[2]) != ptr - argv[2]) {
        fprintf(stderr, "%s: incorrect filemode\n", argv[2]);
        exit(1);
    }
    l = creat(argv[1], p);
    printf("l=%d\n", l); // Команда umask - выводит маску. Команда ls -l filename выводит права файла. Файл создался с правами 664 т.к. маска отнимается от 666
    exit(0);
}