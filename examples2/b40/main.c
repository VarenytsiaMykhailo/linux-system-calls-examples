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

void f() {
    printf("Signal SIGPIPE received\n");
}

// Попытка писать в канал, который ни кем не открыт на чтение
int main() {
    int fd[2];
    signal(SIGPIPE, f);
    pipe(fd);
    close(fd[0]);
    if (write(fd[1], "", 1) == -1) {
        perror("write");
    }
    printf("After write\n"); // Выполнится т.к. на сигнал SIGPIPE установили f
    exit(0);
}
