#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cd cmake-build-debug
// ./task4
int main() {
    int child_pid, return_code;
    printf("I am father before fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
    int fork_result = fork();
    printf("fork_result = %d\n", fork_result);
    int sleep_time = 1;
    if (fork_result) {
        printf("I am father after fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        printf("I go exit\n");
        sleep(sleep_time);
        exit(0);
    } else {
        printf("I am son. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        printf("I go sleep\n");
        sleep(sleep_time + 1);
        printf("I am son. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid()); // Выведет в новом шелле. У Вавренюка ppid у дочернего процесса стал процесс init с pid = 1
        exit(0);
    }
}