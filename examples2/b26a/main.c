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
    int a, b, c;
    sigset_t mask;

    a = 0;
    b = 3;
    c = 7;

    sigemptyset(&mask);
    sigaddset(&mask, SIGFPE);
    sigprocmask(SIG_SETMASK, &mask, NULL); // Устанавливаем маску на SIGFPE (блокирование доставки)

    //c = b/a;
    kill(getpid(), SIGFPE); // Сигнал SIGFPE заблокирован т.к. мы его послали сами. Но если его пошлет ядро, то сигнал доставится
    printf("%d\n", c);
    exit(0);
}
