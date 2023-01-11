#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>

extern int errno;

// ./b43 ./../../b42/cmake-build-debug/fifofile
// Программа на именованный канал, на запись. Именованный канал можно открыть только на чтение или на запись. Одновременно на запись и чтение открыть нельзя
int main(int argc, char *argv[], char *envp[]) {
    struct stat st;
    int f, l;
    char buf[4096];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fifofile\n", argv[0]);
        exit(1);
    }
    if (stat(argv[1], &st) == -1) {
        perror(argv[1]);
        exit(1);
    }
    if (!S_ISFIFO(st.st_mode)) {
        fprintf(stderr, "%s not fifofile\n", argv[1]);
        exit(1);
    }
    printf("Before open\n");
    if ((f = open(argv[1], O_WRONLY | O_NDELAY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    printf("After open\n");
    // Читаем с клавиатуры и пишем в именованный канал
    while ((l = read(0, buf, 4096))) {
        write(f, buf, l);
    }
    close(f);
    exit(0);
}
