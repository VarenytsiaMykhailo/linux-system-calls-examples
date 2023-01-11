#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int main() {
    int fork_result = fork();

    if (fork_result) {
        int rc;
        wait(&rc);
        printf("rc=%x\n", rc);
    } else {
        for (int i = 0; i < 1000; ++i) {
            printf("i = %d\n", i);
            for (int j = 0; j < 1000; ++j) {
                for (int k = 0; k < 1000; ++k) {

                }
            }
        }
    }

    return 0;
}