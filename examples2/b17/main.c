#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// ./b17 и кликаем ctrl+c несколько раз и ждем
void f(int sig) {
    static int l = 0;
    int i, j;
    l++;
    printf("Handler begin %d\n", l);
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
    act.sa_flags = SA_NODEFER; // Don't automatically block the signal when its handler is being executed. Доставка сигналов не будет блокироваться, будет возможен рекурсивный вход
    // прием сигналов будет заблокиррван и только один новый встанет в очередь и начнет свое исполнение после завершения работы обработчика предыдущего сигнала
    sigaction(SIGINT, &act, NULL); // ctrl + слеш
    for (;;);
}
