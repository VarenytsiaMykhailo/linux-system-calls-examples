#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

#define MESSAGE_LENGTH 32

extern int errno;

typedef struct message {
    long type;
    char data[MESSAGE_LENGTH + 1];
} message;

int msqid;

void handler(int sig) {
    printf("Signal handler\n");
    if (sig == SIGINT) {
        printf("Signal SIGINT\n");
        msgctl(msqid, IPC_RMID, 0);
        exit(SIGINT);
    }
    if (sig == SIGTERM) {
        printf("Signal SIGTERM\n");
        msgctl(msqid, IPC_RMID, 0);
        exit(SIGTERM);
    }
}


int main(int argc, char *argv[]) {
    key_t key = ftok(argv[0], 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }

    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);

    message m;

    int fork_result = fork();
    if (fork_result) {
        while (1) {
            m.type = 1;
            printf("%d\n", getpid());
            if (msgsnd(msqid, &m, MESSAGE_LENGTH, 0) == -1) {
                perror("msgsnd");
                //exit(1);
            }
            sleep(1);
            if (msgrcv(msqid, &m, sizeof(m) - 4, 2, 0) == -1) {
                perror("msgrcv");
                //exit(1);
            }
        }
    } else {
        while (1) {
            printf("%d\n", getpid());
            m.type = 2;
            if (msgsnd(msqid, &m, MESSAGE_LENGTH, 0) == -1) {
                perror("msgsnd");
                //exit(1);
            }
            sleep(1);
            if (msgrcv(msqid, &m, sizeof(m) - 4, 1, 0) == -1) {
                perror("msgrcv");
                //exit(1);
            }
        }
    }

    msgctl(msqid, IPC_RMID, 0);
    return 0;
}