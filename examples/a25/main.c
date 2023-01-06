#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// ./a25 ls
// ./a25 ls qwerty123
// ./a25 ./a25 ./a25 ./a25 ./a25
int main(int argc, char *argv[]) {
    int rc;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command args ...\n", argv[0]);
        exit(1);
    }
    if (fork()) {
        wait(&rc);
        printf("rc=%d\n", rc);
        exit(0);
    } else {
        execvp(argv[1], argv + 1);
        perror(argv[1]);
        exit(1);
    }
}