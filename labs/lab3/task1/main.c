#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// ./task1
// Обработчик сигнала
// sig - номер сигнала. Можно устанавливать один обработчик на несколько сигналов. Внутри обработчика можно анализировать какой сигнал пришел
void func(int sig) {
    signal(SIGINT, SIG_DFL); // SIG_DFL - дефолтное поведение, SIG_IGN - сигнал игнорируется. SIGINT - это ctrl + c
    printf("Signal received\n");
}

int main() {
    signal(SIGINT, func);
    for (;;);

    return 0;
}