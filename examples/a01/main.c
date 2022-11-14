#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int l, i;
    // Создает файл. 0 - без прав. Открывает файл на запись
    l = creat("a.txt", 0);
    printf("l=%d\n", l);
    if (l >= 0) {
        // Записываем в созданный файл. Запишется, если файла не существовало
        i = write(l, "test1\n", 6);
        if (i < 0) {
            perror("write");
            printf("write\n");
            printf("errno=%d\n", errno);
        }
        close(l);
    } else {
        perror("creat");
        printf("creat\n");
        printf("errno=%d\n", errno);
        exit(1);
    }
    // Повторное открытие приведет к ошибке т.к. файл уже создан, причем без прав
    l = creat("a.txt",0);
    printf("l=%d\n", l);
    if (l >= 0) {
        i = write(l, "test1\n", 6);
        if (i < 0) {
            perror("write");
            printf("write\n");
            printf("errno=%d\n", errno);
        }
        close(l);
    } else {
        perror("creat");
        printf("creat\n");
        printf("errno=%d\n", errno);
    }
    errno = 9;
    perror("errno");
    printf("errno\n");
    exit(0);
}
