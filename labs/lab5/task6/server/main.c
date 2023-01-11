#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MESSAGE_LENGTH 32

extern int errno;

typedef struct message {
    long type;
    char data[MESSAGE_LENGTH + 1];
} message;

// Просмотр запущенных очередей сообщений:
// ipcs -a
// Удалить очередь:
// ipcrm -q 12
// 12 - msqid
int main(int argc, char *argv[]) {
    key_t key = ftok(argv[0], 'A');

    int msqid = msgget(key, IPC_CREAT | 0600);

    message request;
    message response;


    for (long long int i = 0;; i++) {
        // 4 байта уйдут на message->type
        msgrcv(msqid, &request, sizeof(request) - 4, 0, 0);

        printf("Request got message counter: %lld\n", i);
        printf("Request message type: %ld\n", request.type);
        printf("Request message: %s\n", request.data);

        response.type = 1;
        strcpy(response.data, request.data);

        printf("Formed response message:\n");
        printf("Response message type: %ld\n", response.type);
        printf("Response message: %s\n", response.data);

        msgsnd(request.type, &response, MESSAGE_LENGTH, 0);
    }

    msgctl(msqid, IPC_RMID, 0);
    exit(0);
}