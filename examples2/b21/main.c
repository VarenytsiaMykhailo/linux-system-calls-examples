#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void f(int sig) {
    printf("Segmentation fault\n");
    exit(0);
}

int main() {
    int n = 0;
    int *p;
    struct sigaction act;
    act.sa_handler = f;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGSEGV, &act,
              NULL); // Сигнал SIGFPE - посылается ядром, когда происходит исключение с плавающей точкой (например, при делении на 0)
    p = (int *) f;
    *p = 3; // Перехватываем ошибку
    exit(0);
}
