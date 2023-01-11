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
    long msgInitiator;
    char data[MESSAGE_LENGTH + 1];
} message;

int msqid_request;
int msqid_response;

void handler(int sig) {
    printf("Signal handler\n");
    if (sig == SIGINT) {
        printf("Signal SIGINT\n");
        msgctl(msqid_request, IPC_RMID, 0);
        msgctl(msqid_response, IPC_RMID, 0);
        exit(SIGINT);
    }
    if (sig == SIGTERM) {
        printf("Signal SIGTERM\n");
        msgctl(msqid_request, IPC_RMID, 0);
        msgctl(msqid_response, IPC_RMID, 0);
        exit(SIGTERM);
    }
}

// Просмотр запущенных очередей сообщений:
// ipcs -a
// Удалить очередь:
// ipcrm -q 12
// 12 - msqid
int main(int argc, char *argv[]) {
    key_t key_request = ftok(argv[0], 'A');
    if (key_request == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid_request = msgget(key_request, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }

    key_t key_response = ftok(argv[0], 'B');
    if (key_response == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid_response = msgget(key_response, IPC_CREAT | 0600)) == -1) {
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
        if (msgrcv(msqid_request, &request, sizeof(request) - 4, 0, 0) == -1) {
            perror("msgrcv");
            //exit(1);
        }

        printf("Request got message counter: %lld\n", i);
        printf("Request message type: %ld\n", request.type);
        printf("Request message msgInitiator: %ld\n", request.msgInitiator);
        printf("Request message: %s\n", request.data);

        response.type = request.type;
        response.msgInitiator = request.msgInitiator;
        strcpy(response.data, request.data);

        printf("Formed response message:\n");
        printf("Response message type: %ld\n", response.type);
        printf("Response message msgInitiator: %ld\n", response.msgInitiator);
        printf("Response message: %s\n", response.data);

        if (msgsnd(msqid_response, &response, MESSAGE_LENGTH, 0) == -1) {
            perror("msgsnd");
            //exit(1);
        }
    }

    msgctl(msqid_request, IPC_RMID, 0);
    msgctl(msqid_response, IPC_RMID, 0);
    exit(0);
}