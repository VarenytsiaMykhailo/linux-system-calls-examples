#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// ps
int main() {
    printf("I am father before fork. My pid=%d ppid=%d\n", getpid(), getppid());
    int fork_result = fork();
    printf("fork_result = %d\n", fork_result);
    if (fork_result) {
        printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
        wait(NULL);
        exit(0);
    } else {
        printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid());
        exit(0);
    }
}
