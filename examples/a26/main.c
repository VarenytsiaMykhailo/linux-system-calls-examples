#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Запуск программы с измененным окружением
// env
// Затем запускаем программу. Окружение изменилось и теперь состоит только из трех переменных
int main() {
    char *env[] = {"A=1", "B=2", "C=3", NULL}; // Массив должен обязательно завершиться нуллом
    if (fork()) {
        wait(NULL);
        exit(0);
    } else {
        execle("/usr/bin/env", "env", NULL, env);
        perror("/usr/bin/env"); // Выполнится в случае, если execle завершится неудачно
        exit(1);
    }
}