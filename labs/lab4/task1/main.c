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
    int fd1[2]; // fd1: parent[1] --> child[0]
    int fd2[2]; // fd2: parent[0] <-- child[1]

    pipe(fd1);
    pipe(fd2);

    int fork_result = fork();
    if (fork_result) {
        close(fd1[0]);
        close(fd2[1]);
        const char *buf = "Message from father to child";
        write(fd1[1], buf, strlen(buf));

        char message_from_child[4096] = {};
        read(fd2[0], message_from_child, 4096);

        printf("Got message from child: %s\n", message_from_child);

        close(fd1[1]);
        close(fd2[0]);
    } else {
        close(fd1[1]);
        close(fd2[0]);

        char message_from_father[4096] = {};
        read(fd1[0], message_from_father, 4096);
        printf("Got message from father: %s\n", message_from_father);

        const char *buf = "Message from child to father";
        write(fd2[1], buf, strlen(buf));

        close(fd1[0]);
        close(fd2[1]);
    }

    return 0;
}