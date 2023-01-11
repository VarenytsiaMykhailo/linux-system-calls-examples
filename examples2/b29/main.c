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

sigset_t myset;

void showpending(int sig) {
    int i;
    sigset_t mask;
    sigpending(&mask); // Получаем маску пришедших сигналов, но их временная доставка заблокирована
    printf("\n2345678\n");
    // Заблокировали доставку сигналов. Смотрим, какие сигналы хза определенное время к нам пришли
    for (i = 2; i < 9; i++) {
        printf("%d", sigismember(&mask, i));
    }
    printf("\n");
}

// Очищает маску сигналов
void clearpending(int sig) {
    int i;
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    // Временно устанавливаем на все сигналы диспозицию игнорирования
    for (i = 2; i < 9; i++) {
        sigaction(i, &act, NULL);
    }
    sigprocmask(SIG_UNBLOCK, &myset, NULL);
    sigprocmask(SIG_BLOCK, &myset, NULL);
    act.sa_handler = SIG_DFL;
    for (i = 2; i < 9; i++) {
        sigaction(i, &act, NULL);
    }
}

// Запускаем в фоновом режиме. По сигналу SIGUSR1 - показываем какие сигналы пришли, но их доставка пока заблокирована. По SIGHUP очищает сигналы
// ./b29 &
// kill -10 10248
// kill -3 10248
// kill -10 10248
// kill -5 10248
// kill -10 10248
// kill -7 10248
// kill -10 10248
// kill -1 10248
// kill -10 10248
// -10 - сигнал SIGUSR1, -1 - сигнал SIGHUP

// kill 10248
// kill 10248 - завершает процесс
int main() {
    int i;
    struct sigaction act;

    // Создаем маску сигналов
    sigemptyset(&myset);
    for (i = 2; i < 9; i++) {
        sigaddset(&myset, i);
    }

    act.sa_handler = showpending;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);

    act.sa_handler = clearpending;
    sigaction(SIGHUP, &act, NULL);

    sigprocmask(SIG_SETMASK, &myset, NULL);

    for (;;)
        pause();

}
