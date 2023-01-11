#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

extern int errno;

int main() {
    int fork_result = fork();
    if (fork_result) {
        printf("Parent pid = %d Son pid = %d\n", getpid(), fork_result);
        printf("setpgrp return %d\n", setpgrp());
        printf("I am father. my pgid = %d sid = %d\n", getpgrp(), getsid(getpid()));
        pause();
    } else {
        printf("I am son. my pgid = %d sid = %d\n", getpgrp(), getsid(getpid()));
        setpgrp(); // Создает новую группу процессов и дочерний процесс становится лидером новой группы процессов
        printf("I am son. my pgid = %d sid = %d\n", getpgrp(), getsid(getpid()));
        fork();
        pause();
    }
}
