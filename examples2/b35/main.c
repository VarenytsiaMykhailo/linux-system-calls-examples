#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>

int i;

void f() {
    printf("%d\n", i); // Размер канала
    exit(0);
}

// Измерение емкости канала.
int main() {
    int fd[2];

    signal(SIGALRM, f);
    alarm(1);
    pipe(fd);
    // Пишем в канал до тех пор, пока он не заблокируется. write вернет -1, когда емкость будет заполнена
    for (i = 0; write(fd[1], "", 1) != -1; i++);
}
