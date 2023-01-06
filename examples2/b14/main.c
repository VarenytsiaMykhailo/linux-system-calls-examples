#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// ./b14
// Обработчик сигнала
void f(int sig) { // sig - номер сигнала. Можно устанавливать один обработчик на несколько сигналов. Внутри обработчика можно анализировать какой сигнал пришел
    signal(SIGINT, SIG_DFL); // SIG_DFL - дефолтное поведение, SIG_IGN - сигнал игнорируется. SIGNINT - диспозиция. SIGINT - это ctrl + c
    printf("Signal received\n");
}

int main() {
    signal(SIGINT, f);
    for (;;);
}
