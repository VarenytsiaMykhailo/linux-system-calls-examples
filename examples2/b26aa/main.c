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

void handler(int sig) {
}

int main() {
    int a, b, c;
    sigset_t mask;

    a = 0;
    b = 3;
    c = 7;

    signal(SIGFPE, handler);
    c = b/a; // Произойдет зацикливание т.к. из обработчика мы попадаем на эту строчку повторно

    printf("%d\n", c);
    exit(0);
}
