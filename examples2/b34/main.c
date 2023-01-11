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

// Родительский процесс будет читать из канала и писать на экран, дочерний - читать с экрана (ввод с клаиватуры), писать в канал
int main() {
    int p, l;
    char buf[80];
    int fd[2]; // fd[0] - дескриптор на чтение, fd[1] - дескриптор на запись
    pipe(fd);
    int fork_result = fork();
    // Родительский процесс будет читать из канала и писать на экран, дочерний - читать с экрана (ввод с клаиватуры), писать в канал
    if (fork_result) {
        close(fd[1]); // Закрываем дескриптор на запись
        while ((l = read(fd[0], buf, 80)) > 0) {
            write(1, buf, l); // Пишем на экран что прочитали
        }
        close(fd[0]);
        wait(NULL);
        exit(0);
    } else {
        close(fd[0]); // Закрываем дескриптор на чтение
        while ((l = read(0, buf, 80)) > 0) {
            write(fd[1], buf, l); // Читает с экрана и пишет что прочитал в канал
        }
        close(fd[1]);
        exit(0);
    }
}
