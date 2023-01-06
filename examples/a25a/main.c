#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// ./a25a build.ninja cat
int main(int argc, char *argv[]) {
    int rc;
    if (argc < 3) {
        fprintf(stderr, "Usage: %s infile command args ...\n", argv[0]);
        exit(1);
    }
    close(0); // Закрываем стандартный ввод
    if (open(argv[1], O_RDONLY) == -1) { // Стандартный ввод теперь будет из файла
        perror(argv[1]);
        exit(1);
    }
    if (fork()) {
        wait(&rc);
        printf("rc=%d\n", rc);
        exit(0);
    } else {
        execvp(argv[2], argv + 2);
        perror(argv[2]);
        exit(1);
    }
}