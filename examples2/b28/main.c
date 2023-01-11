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

// Для SIGCHLD
void w(int sig) {
    int rc;
    wait(&rc);
    printf("rc=%d\n", rc);
}

void f(int sig) {
    int i, j;
    printf("Begin sig=%d\n", sig);
    for (i = 0; i < 0x7fff; i++);
    printf("End sig=%d\n", sig);
}

int main() {
    int p, rc;
    struct sigaction act;
    sigset_t mask;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGHUP, &act, NULL);

    act.sa_handler = f;
    sigaction(SIGINT, &act, NULL);

    act.sa_handler = SIG_DFL;
    sigaction(SIGQUIT, &act, NULL);

    act.sa_handler = w;
    sigaction(SIGCHLD, &act, NULL);

    int fork_result = fork();
    if (fork_result) {
        sleep(1);

        printf("Send SIGHUP\n");
        kill(fork_result, SIGHUP);
        sleep(1);

        printf("Send SIGINT\n");
        kill(fork_result, SIGINT);
        sleep(1);

        printf("Send SIGQUIT\n");
        kill(fork_result, SIGQUIT);
        sleep(1);

        exit(0);
    } else {
        execl("./../../b28a/cmake-build-debug/b28a", "./../../b28a/cmake-build-debug/b28a", NULL);
        perror("exec");
        exit(1);
    }

}
