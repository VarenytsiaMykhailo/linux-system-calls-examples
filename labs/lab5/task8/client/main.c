#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#define MESSAGE_LENGTH 32

extern int errno;

typedef struct message {
    long type;
    char data[MESSAGE_LENGTH + 1];
} message;

int msqid_server;
int msqid_client;

unsigned int msqIdSendTo = 0;

message request;
message response;
int flag = 0;

void read_data_and_send_message() {
    flag = 1;

    printf("Enter msqIdSendTo to send:\n");
    //scanf("%d\n", &msqIdSendTo);
    //fflush (stdin);
    //printf("\n");
    char msqIdSendTo2[MESSAGE_LENGTH + 1];
    char *resMsqIdSendTo = fgets(msqIdSendTo2, MESSAGE_LENGTH, stdin);
    char *end;
    msqIdSendTo = strtol (msqIdSendTo2, &end, 10);
    printf("Input msqIdSendTo: %d\n", msqIdSendTo);

    //request.type = msqid_client;
    request.type = msqIdSendTo;

    printf("Enter message to send:\n");
    char *res = fgets(request.data, MESSAGE_LENGTH, stdin);
    if (res == NULL) {
        perror("fgets");
    }
    printf("Input data res: %s\n", res);
    printf("Sending...");

    if (msgsnd(msqid_server, &request, MESSAGE_LENGTH, 0) == -1) {
        perror("msgsnd");
        //exit(1);
    }
}

void handler(int sig) {
    printf("Signal handler\n");
    if (sig == SIGINT) {
        printf("Signal SIGINT\n");
        // Клиенты не должны удалять очередь сервера
        //msgctl(msqid_server, IPC_RMID, 0);
        msgctl(msqid_client, IPC_RMID, 0);
        exit(SIGINT);
    }
    if (sig == SIGTERM) {
        printf("Signal SIGTERM\n");
        // Клиенты не должны удалять очередь сервера
        //msgctl(msqid_server, IPC_RMID, 0);
        msgctl(msqid_client, IPC_RMID, 0);
        exit(SIGTERM);
    }
    if (sig == SIGTSTP) {
        printf("Signal SIGTSTP\n");
        read_data_and_send_message();
    }
}

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
    if (server_key == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid_server = msgget(server_key, 0)) == -1) {
        perror("msgget");
        exit(1);
    }
    if ((msqid_client = msgget(IPC_PRIVATE, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }

    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);


    while (1) {
        //strcpy(request.data, argv[2]);
        sleep(delay);

        if (msgrcv(msqid_client, &response, sizeof(request) - 4, 0, 0) == -1) {
            if (flag == 0) {
                perror("msgrcv");
                exit(1);
            }
        }

        if (flag == 0) {
            printf("Got response message:\n");
            printf("Response message type: %ld\n", response.type);
            printf("Response message: %s\n", response.data);
        }
        flag = 0;
    }

    // Клиенты не должны удалять очередь сервера
    //msgctl(msqid_server, IPC_RMID, 0);
    msgctl(msqid_client, IPC_RMID, 0);

    exit(0);
}