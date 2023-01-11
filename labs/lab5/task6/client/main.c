#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

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
// ./client ./../../server/cmake-build-debug/server qwerty 1
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s serverFile message delay\n", argv[0]);
        exit(1);
    }

    char *ptr;
    unsigned int delay = strtol(argv[3], &ptr, 0);
    if (strlen(argv[3]) != ptr - argv[3]) {
        fprintf(stderr, "%s: incorrect delay\n", argv[3]);
        exit(1);
    }

    key_t server_key = ftok(argv[1], 'A');
    int msqid_server = msgget(server_key, 0);

    int msqid_client = msgget(IPC_PRIVATE, IPC_CREAT | 0600);

    message request;
    message response;

    strcpy(request.data, argv[2]);
    request.type = msqid_client;

    msgsnd(msqid_server, &request, MESSAGE_LENGTH, 0);
    sleep(delay);
    msgrcv(msqid_client, &response, sizeof(request) - 4, 0, 0);

    printf("Formed response message:\n");
    printf("Response message type: %ld\n", response.type);
    printf("Response message: %s\n", response.data);

    msgctl(msqid_client, IPC_RMID, 0);

    exit(0);
}