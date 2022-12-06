#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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