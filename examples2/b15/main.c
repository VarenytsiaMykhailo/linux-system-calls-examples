#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// ./b15
// Обработчик сигнала
// sig - номер сигнала. Можно устанавливать один обработчик на несколько сигналов. Внутри обработчика можно анализировать какой сигнал пришел
void f(int sig) {
    //signal(SIGINT, SIG_DFL);
    printf("Signal received\n");
}

int main() {
    struct sigaction act; // Механизм надежных сигналов, не требующий переустановку обработчика в дефолт. Обработчик будет однократным
    act.sa_handler = f;
    //sigemptyset(&act.sa_mask); // Отвязываем сигналы
    act.sa_flags = SA_RESETHAND; // Обработчик установится только на первый сигнал, затем работа сигнала установится в дефолт
    sigaction(SIGINT, &act, NULL);
    for (;;);
}