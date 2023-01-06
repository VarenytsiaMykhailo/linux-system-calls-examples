#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {
    int rc;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command args ...\n", argv[0]);
        exit(1);
    }
    int fork_result = fork();
    if (fork_result) {
        printf("father\n");
        printf("parameters:\n");
        for (char **it = argv; *it; ++it) {
            printf("%s\n", *it);
        }
        printf("env\n");
        for (char **it = envp; *it; it++) {
            printf("%s\n", *it);
        }

        wait(&rc);
        printf("rc=%d\n", rc);
        exit(0);
    } else {
        printf("\n\n\n\n__________________________----son");
        execvp(argv[1], argv + 1);
        perror(argv[1]);
        exit(1);
    }
}