#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>


int main() {
    int fd[2];
    pipe(fd);

    int fork_result = fork();
    if (fork_result) {
        close(fd[1]);

        char message_from_child[80] = {};

        while (1) {
            int n = read(fd[0], message_from_child, 80);
            printf("Got message from child: %s\n", message_from_child);
        }

        close(fd[0]);
    } else {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execl("./../../task4exec/cmake-build-debug/task4exec", "./../../task4exec/cmake-build-debug/task4exec", NULL);
    }

    return 0;
}