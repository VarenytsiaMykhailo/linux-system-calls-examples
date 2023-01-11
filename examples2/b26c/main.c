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

int main() {
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    // Пробуем установить SIG_IGN на SIGKILL с помощью signal и sigaction. SIGKILL нельзя игнорировать, поэтому будет ошибка.
    printf("%d\n", signal(SIGKILL, SIG_IGN));
    perror("signal");

    printf("%d\n", sigaction(SIGKILL, &act, NULL));
    perror("signal");

    exit(0);
}