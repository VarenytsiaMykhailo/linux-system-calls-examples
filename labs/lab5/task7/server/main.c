#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>

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

// Просмотр запущенных очередей сообщений:
// ipcs -a
// Удалить очередь:
// ipcrm -q 12
// 12 - msqid
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

    message request;
    message response;


    for (long long int i = 0;; i++) {
        // 4 байта уйдут на message->type
        if (msgrcv(msqid, &request, sizeof(request) - 4, 0, 0) == -1) {
            perror("msgrcv");
            //exit(1);
        }
        printf("Request got message counter: %lld\n", i);
        printf("Request message type: %ld\n", request.type);
        printf("Request message: %s\n", request.data);

        response.type = 1;
        strcpy(response.data, request.data);

        printf("Formed response message:\n");
        printf("Response message type: %ld\n", response.type);
        printf("Response message: %s\n", response.data);

        if (msgsnd(request.type, &response, MESSAGE_LENGTH, 0) == -1) {
            perror("msgsnd");
            //exit(1);
        }
    }

    msgctl(msqid, IPC_RMID, 0);
    exit(0);
}