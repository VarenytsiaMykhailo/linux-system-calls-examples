#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// ./b17 и кликаем ctrl+c несколько раз и ждем
void f(int sig) {
    sigset_t mask; // Создаем маску
    static int l = 0;
    int i, j;
    l++;
    printf("Handler begin %d\n", l);
    sigemptyset(&mask); // Очищаем маску сигналов
    sigaddset(&mask, SIGUSR2); // Добавляем к маске сигналов SIGUSER2: в маске сигналов установлен один бит для SIGUSR2
    sigprocmask(SIG_BLOCK, &mask, NULL); // SIG_BLOCK означает, что какие-то сигналы могут быть уже заблокированы и к текущей маске сигналов добавляется SIGUSR2
    // Имитируем задержку
    for (i = 0; i < 0x7fff; i++) {
        for (j = 0; j < 0xffff; j++);
    }
    printf("Handler end%d\n", l);
    l--;
}

int main() {
    struct sigaction act; // Механизм надежных сигналов, не требующий переустановку обработчика в дефолт. Обработчик будет однократным
    act.sa_handler = f;
    sigemptyset(&act.sa_mask); // Маска сигналов обнулена
    sigaddset(&act.sa_mask, SIGUSR1);
    act.sa_flags = SA_NODEFER; // Don't automatically block the signal when its handler is being executed. Доставка сигналов не будет блокироваться, будет возможен рекурсивный вход
    // прием сигналов будет заблокиррван и только один новый встанет в очередь и начнет свое исполнение после завершения работы обработчика предыдущего сигнала
    sigaction(SIGINT, &act, NULL); // ctrl + слеш
    for (;;);
}
