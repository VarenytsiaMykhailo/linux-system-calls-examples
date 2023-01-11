#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

void body(pid_t pid) {
    pid_t this_pid = getpid();

    sigset_t ss;
    sigemptyset(&ss);

    if (this_pid < pid) {
        sigsuspend(&ss);
    }

    while (1) {
        printf("%d\n", this_pid);
        sleep(rand() % 5);
        kill(pid, SIGUSR1);
        sigsuspend(&ss);
    }
}

void f(int sig) {
    if (sig == SIGUSR1) {
        printf("SIGUSR1\n");
    } else {
        signal(sig, SIG_DFL);
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = f;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);

    int parent_pid = getpid();
    int fork_result = fork();
    if (fork_result) {
        body(fork_result);
    } else {
        body(parent_pid);
    }

    return 0;
}