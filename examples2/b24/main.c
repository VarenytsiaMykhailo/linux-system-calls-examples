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

void f(int sig) {
    printf("sig=%d\n", sig);
}

int main() {
    struct sigaction act;
    sigset_t mask;
    act.sa_handler = f;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGHUP, &act, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGHUP);
    sigprocmask(SIG_SETMASK, &mask, NULL); // Устанавливаем маску на SIGHUP

    kill(getpid(), SIGHUP); // Обработчик вызван не будет т.к. мы заблокировали доставку сигнала SIGHUP, но система запомнит, что сигнал пришел.
    printf("Signal send\n");
    sleep(1);

    sigdelset(&mask, SIGHUP);
    printf("Delete mask\n");
    sigprocmask(SIG_SETMASK, &mask, NULL); // Снимаем маску на SIGHUP. Разблокировали доставку SIGHUP и на этом месте вызовется обработчик

    sleep(1);
    exit(0);
}
