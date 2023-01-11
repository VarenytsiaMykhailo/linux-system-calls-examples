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

void f(int a) {
    printf("Signal received %d\n", a);
}

int main() {
    int pid, rc;
    // Устанавливаем на три сигнала обработчик (но на 9ый он установится). Вызовятся ли обработчики для 3 и 8го?
    signal(3, f);
    signal(8, f);
    signal(9, f);
    pid = fork();
    if (pid) {
        // Посылаем сразу три сигнала дочернему процессу и смотри по какому он завершится
        kill(pid, 8);
        kill(pid, 3);
        kill(pid, 9);
        wait(&rc);
        printf("rc=%d\n", rc);
    } else {
        sleep(1);
    }

    exit(0);
}
