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
    struct sigaction act;

    a = 0;
    b = 3;
    c = 7;

    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    printf("%d\n", sigaction(SIGFPE, &act, NULL));

    c = b/a;
    //kill(getpid(), SIGFPE); // Сигнал SIGFPE заблокирован т.к. мы его послали сами. Но если его пошлет ядро, то сигнал доставится
    printf("%d\n", c);
    exit(0);
}
