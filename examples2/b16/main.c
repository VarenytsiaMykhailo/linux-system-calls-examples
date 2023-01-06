#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void f(int sig) {
    int i, j;
    printf("Handler begin\n");
    // Имитируем задержку
    for (i = 0; i < 0x7fff; i++) {
        for (j = 0; j < 0xffff; j++);
    }
    printf("Handler end\n");
}

int main() {
    struct sigaction act; // Механизм надежных сигналов, не требующий переустановку обработчика в дефолт. Обработчик будет однократным
    act.sa_handler = f;
    sigemptyset(&act.sa_mask); // Маска сигналов обнулена
    act.sa_flags = 0; // Флагов нет
    // прием сигналов будет заблокиррван и только один новый встанет в очередь и начнет свое исполнение после завершения работы обработчика предыдущего сигнала
    sigaction(SIGINT, &act, NULL); // ctrl + слеш
    for (;;);
}
