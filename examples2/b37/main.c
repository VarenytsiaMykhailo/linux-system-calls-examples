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

// Измерение емкости канала.
int main() {
    int fd[2], i;

    pipe(fd);

    fcntl(fd[1], F_SETFL, O_NDELAY); // Переводим дескриптор на запись в неблокирующий режим

    // write вернет -1, когда емкость будет заполнена
    for (i = 0; write(fd[1], "", 1) != -1; i++);
    printf("%d\n", i);
    exit(0);
}
