#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cd cmake-build-debug
// ./task5
int main() {
    int child_pid, return_code;
    printf("I am father before fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
    // wait возвращает id дочернего процесса когда он помрет или -1 в случае ошибки
    printf("I am father. Syscall \"wait\" return %d\n", wait(&return_code));
    int fork_result = fork();
    printf("fork_result = %d\n", fork_result);
    if (fork_result) {
        printf("I am father after fork. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        sleep(1);
        printf("I am father. See zombie where.\n");
        system("ps"); //   35615 ?        00:00:00 task5 <defunct> - зомби процесс


        int command_size = 20;
        char command[command_size];
        for (int i = 0; i < command_size; ++i) {
            command[i] = '\0';
        }
        sprintf(command, "kill %d", fork_result);
        printf("command: %s", command);
        sleep(1);
        system(command);
        sleep(1);
        system("ps");



        exit(0);
    } else {
        printf("I am son. My pid=%d ppid=%d gid=%d\n", getpid(), getppid(), getgid());
        printf("I am son. I exit with code 3\n");
        exit(3);
    }
}

/*
int main() {
    printf("I am father before fork. My pid=%d ppid=%d\n", getpid(), getppid());
    int fork_result = fork();
    printf("fork_result = %d\n", fork_result);
    if (fork_result) {
        printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
        sleep(1);
        printf("I am father. See zombie where.\n");
        system("ps"); //   35615 ?        00:00:00 a19 <defunct> - зомби процесс
        exit(0);
    } else {
        printf("I am son. I exit with code 3\n");
        exit(3);
    }
}
 */