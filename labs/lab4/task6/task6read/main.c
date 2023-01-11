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

// Для создания файла фифо:
// mkfifo fifofile
// Программа на именованный канал, на чтение. Именованный канал можно открыть только на чтение или на запись. Одновременно на запись и чтение открыть нельзя
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
    if ((f = open(argv[1], O_RDONLY | O_NDELAY)) == -1) {
        perror(argv[1]);
        exit(1);
    }
    printf("After open\n");
    // Читаем до тех пор, пока с другой стороны не закроют дескриптор на запись
    while ((l = read(f, buf, 4096))) {
        write(1, buf, l);
    }
    close(f);
    exit(0);
}
