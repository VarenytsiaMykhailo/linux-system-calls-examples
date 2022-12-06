#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int f1, f2;
    char c;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if ((f1 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    f2 = dup(f1);
    printf("f1=%d\nf2=%d\n", f1, f2);
    while (read(f1, &c, 1) > 0)
        write(1, &c, 1);
    printf("Separator\n");
    while (read(f2, &c, 1) > 0) // Ничего не выведет т.к. предыдущий цикл сместил указатель в конец файла и новый цикл ничего не прочтет
        write(1, &c, 1);
    close(f1);
    close(f2);
    exit(0);
}