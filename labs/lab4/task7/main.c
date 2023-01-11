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
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    printf("filename = %s\n", filename);
    char letters[] = {'a', 'b', 'c', 'd', 'e'};

    int fd = creat(filename, 0666);
    close(fd);

    int fork_result = fork();
    if (fork_result) {
        int fd = open(filename, O_WRONLY);
        if (fd == -1) {
            perror("open");
        }

        for (int i = 0; i < 100; i++) {
            if (write(fd, &letters[i % 5], 1) == -1) {
                perror("write");
            }
        }
        close(fd);
        wait(NULL);

    } else {
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
        }
        char buf[1];
        int r;
        while ((r = read(fd, buf, 1) > 0)) {
            //printf("%c", buf[0]);
            write(1, buf, 1);
        }
        close(fd);
    }
}