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

int main() {
    int fd[2];
    char c;
    pipe(fd);
    fcntl(fd[0], F_SETFL, O_NDELAY); // Переводим дескриптор на чтение в неблокирующий режим
    if (read(fd[0], &c, 1) == -1) {
        perror("read"); // read: Resource temporarily unavailable
    }
    printf("After read\n"); // Выполнится
    exit(0);
}
