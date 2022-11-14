#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int f, l;
    char buf[1024];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
    if ((f = creat(argv[1], 0600)) == -1) {
        perror(argv[1]);
        printf("error %s", argv[1]);
        exit(1);
    }
    write(f, "test1\n", 6);
    lseek(f, 0, SEEK_SET);
    l = read(f, buf, 10); // Читать через этот дескриптор нельзя т.к. creat открывает файл только на запись
    printf("l=%d\n", l);
    close(f);
    if ((f = open(argv[1], O_RDONLY)) == -1) { // Открываем файл заново
        perror(argv[1]);
        printf("error %s", argv[1]);
        exit(1);
    }
    l = read(f, buf, 10); // Чтение успешно
    printf("l=%d\n", l);
    write(1, buf, l);
    close(f);
    exit(0);
}