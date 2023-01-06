#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// ./task6 &   для запуска в фоне (для проверки затем ps)
int main() {
    int child_pid, return_code;
    printf("I am father before fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
    // wait возвращает id дочернего процесса когда он помрет или -1 в случае ошибки
    printf("I am father. Syscall \"wait\" return %d\n", wait(&return_code));
    int fork_result = fork();
    printf("fork_result = %d\n", fork_result);
    if (fork_result) {
        printf("I am father after fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        pause();
        printf("I am father. I go wait for son\n");
        child_pid = wait(&return_code);
        printf("I am father. My son with pid %d exit with code 0x%x\n", child_pid, return_code);
        exit(0);
    } else {
        printf("I am son. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        pause();
        printf("I am son. I exit with code 3\n");
        exit(3);
    }
}