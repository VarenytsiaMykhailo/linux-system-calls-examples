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
    // 0 - дескриптор на чтение, 1 - на запись
    //int fd1[2]; // fd1: parent[1] --> child[0]
    int fd2[2]; // fd2: parent[0] <-- child[1]

    //pipe(fd2);
    pipe2(fd2, O_NONBLOCK);
    int fork_result = fork();
    if (fork_result) {
        close(fd2[1]);

        char message_from_child[80] = {};

        while (1) {
            int n = read(fd2[0], message_from_child, 80);
            printf("Got message from child: %s\n", message_from_child);
        }

        close(fd2[0]);
    } else {
        close(fd2[0]);

        char buf[80] = {};

        while (1) {
            int n = read(STDIN_FILENO, buf, 80);
            write(fd2[1], buf, n);
        }

        close(fd2[1]);
    }

    return 0;
}