#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// For test run in cmd:
// for i in {1..1000}; do ./a17; done
int main() {
    char buf[10];
    sprintf(buf, ".tmp%d", getpid());
    close(creat(buf, 0600));
    // Временный файл создан
    int fork_result = fork(); // Порождаем дочерний процесс
    // Два процесса (родитель и сын) пытаются удалить файл. Тот, кто первый удалит - напечатает в консоль, у второго будет ошибка
    if (unlink(buf) != -1) {
        write(1, fork_result ? "#" : "*", 1); // # - для родительского процесса, * - для дочернего
    }

    exit(0);
}