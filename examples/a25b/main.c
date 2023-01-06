#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    int rc;
    if (argc < 3) {
        fprintf(stderr, "Usage: %s outfile command args ...\n", argv[0]);
        exit(1);
    }
    close(1); // Закрываем стандартный вывод
    if (creat(argv[1], 0600) == -1) { // Теперь стандартный вывод будет осуществляться в файл
        perror(argv[1]);
        exit(1);
    }
    if (fork()) {
        wait(&rc);
        fprintf(stderr, "rc=%d\n", rc); // Способ вывести rc в консоли (принтф напечатал бы в файл)
        exit(0);
    } else {
        execvp(argv[2], argv + 2);
        perror(argv[2]);
        exit(1);
    }
}