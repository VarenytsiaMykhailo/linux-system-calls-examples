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
    int pid, rc;
    if (pid = fork()) {
        // Посылаем сразу три сигнала дочернему процессу и смотри по какому он завершится
        kill(pid, 8);
        kill(pid, 9);
        kill(pid, 3);
        wait(&rc);
        printf("rc=%d\n", rc);
    } else {
        sleep(1);
    }

    exit(0);
}
