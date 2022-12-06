#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// cd cmake-build-debug
// ./a21
int main() {
    printf("I am father before fork. My pid=%d ppid=%d\n", getpid(), getppid());
    if (fork()) {
        printf("I am father after fork. My pid=%d ppid=%d\n", getpid(), getppid());
        printf("I go exit\n");
        sleep(1);
        exit(0);
    } else {
        printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid());
        printf("I go sleep\n");
        sleep(2);
        printf("I am son. My pid=%d ppid=%d\n", getpid(), getppid()); // Выведет в новом шелле. Родителем у дочернего процесса станет либо init с ppid = 1, либо окружение CLion
        exit(0);
    }
}