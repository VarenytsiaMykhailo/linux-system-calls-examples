#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void f(int sig) {
    if (sig == SIGUSR1) {
        for (int i = 0; i < 10000; i++) {
            printf("i = %d\n", i);
            for (int j = 0; j < 1; j++) {
                for (int k = 0; k < 1; k++) {

                }
            }
        }
    } else {
        signal(sig, SIG_DFL);
    }
}


int main() {
    int fork_result = fork();
    if (fork_result) {
        sleep(1);
        kill(fork_result, SIGUSR1);
        int rc;
        wait(&rc);
        printf("rc %d\n", rc);
    } else {
        signal(SIGUSR1, f);

        pause();
        exit(0);
    }

    return 0;
}