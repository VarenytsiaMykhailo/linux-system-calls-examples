#include <stdio.h>
#include <stdlib.h>
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
    // Не используем dup, а просто открываем файл второй раз
    // open всегда создает новую запись в системной таблице => указатели на чтение и запись у f1 и f2 у каждого свои, второй цикл отработает.
    if ((f2 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    printf("f1=%d\nf2=%d\n", f1, f2);
    while (read(f1, &c, 1) > 0)
        write(1, &c, 1);
    write(1, "Separator\n", 10);
    while (read(f2, &c, 1) > 0)
        write(1, &c, 1);
    close(f1);
    close(f2);
    exit(0);
}