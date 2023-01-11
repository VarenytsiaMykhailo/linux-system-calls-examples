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

// Аналог: who | wc -l
int main() {
    int fd[2];
    pipe(fd);

    int fork_result = fork();
    // Родитель - читает, сын - пишет
    if (fork_result) {
        close(fd[1]);
        close(0);
        dup(fd[0]); // Связываем fd[0] с стандартным дескриптором на чтение 0
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL); // wc - подсчитывает количество строк подаваемых на стандартный ввод
        perror("wc");
        exit(1);
    } else {
        close(fd[0]);
        close(1);
        dup(fd[1]); // Связываем fd[1] с стандартным дескриптором на запись 1
        close(fd[1]);
        execlp("who", "who", NULL); // who - выводит список пользователей, но уже не на стандартный вывод, а в канал
        perror("who");
        exit(1);
    }
}
