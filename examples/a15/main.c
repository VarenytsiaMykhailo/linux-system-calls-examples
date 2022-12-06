#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int f, l;
    char buf[20];
    struct stat st;
    if ((f = creat("tmpfile", 0777)) == -1) {
        perror("tmpfile");
        exit(1);
    }
    write(f, "test\n", 5);
    close(f);
    if ((f = open("tmpfile", O_RDONLY)) == -1) {
        perror("tmpfile");
        exit(1);
    }
    l = read(f, buf, 20);
    write(1, buf, l);
    fstat(f, &st);
    printf("nlink=%d\n", st.st_nlink);
    unlink("tmpfile"); // Удаляет жесткую ссылку на файл. В unix нет системного вызова для полного удаления файла
    fstat(f, &st);
    printf("nlink=%d\n", st.st_nlink);
    lseek(f, 0, SEEK_SET);
    l = read(f, buf, 20);
    write(1, buf, l);
    close(f);
    exit(0);
}