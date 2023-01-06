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

// ./b18 и кликаем ctrl+c несколько раз и ждем
void f(int sig) {
    int pid, rc;
    pid = wait(&rc);
    printf("My son %d with code 0x%x exited\n", pid, rc);
}

int main() {
    int p, fl, n;
    char status[256], buf[4096];

    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, NULL);

    if (!(p = fork())) {
        exit(1);
    }
    // Спим, чтобы дочерний процесс гарантированно завершился. Как только дочерний процесс стал зомбил, вызывается обработчик на SIGCHLD, который выполнит wait
    sleep(2);
    snprintf(status, 256, "/proc/%d/status", p);
    if ((fl = open(status, O_RDONLY)) != -1) {
        n = read(fl, buf, 4096), write(1, buf, n), close(fl);
    } else {
        perror(status);
    }

    return 0;
}
