#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// Файл с дырой
int main(int argc, char *argv[]) {
    int f, l;
    char *ptr;
    char buf[1024];
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file size\n", argv[0]);
        exit(1);
    }
    l = strtol(argv[2], &ptr, 0); // Последний параметр - система исчисления. 0 - выбирается автоматически
    if (strlen(argv[2]) != ptr - argv[2]) {
        fprintf(stderr, "%s: incorrect size\n", argv[2]);
        exit(1);
    }
    if ((f = creat(argv[1], 0600)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    write(f, "1", 1);
    lseek(f, l, SEEK_SET);
    write(f, "1", 1);
    close(f);
    exit(0);
}