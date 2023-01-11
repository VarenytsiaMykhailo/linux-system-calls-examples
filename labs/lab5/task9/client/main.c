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
    long msgInitiator;
    char data[MESSAGE_LENGTH + 1];
} message;

int msqid_request;
int msqid_response;

unsigned int pidSendTo = 0;

message request;
message response;

int flag = 0;

void read_data_and_send_message() {
    flag = 1;

    printf("Enter pidSendTo to send:\n");
    //scanf("%d\n", &msqIdSendTo);
    //fflush (stdin);
    //printf("\n");
    char pidSendTo2[MESSAGE_LENGTH + 1];
    char *resPidSendTo= fgets(pidSendTo2, MESSAGE_LENGTH, stdin);
    char *end;
    pidSendTo = strtol (pidSendTo2, &end, 10);
    printf("Input pidSendTo: %d\n", pidSendTo);

    request.type = pidSendTo;
    request.msgInitiator = getpid();

    printf("Enter message to send:\n");
    char *res = fgets(request.data, MESSAGE_LENGTH, stdin);
    if (res == NULL) {
        perror("fgets");
    }
    printf("Input data res: %s\n", res);
    printf("Sending...\n");

    if (msgsnd(msqid_request, &request, MESSAGE_LENGTH, 0) == -1) {
        perror("msgsnd");
        //exit(1);
    }
}

void handler(int sig) {
    printf("Signal handler\n");
    if (sig == SIGINT) {
        printf("Signal SIGINT\n");
        // Клиенты не должны удалять очередь
        //msgctl(msqid_request, IPC_RMID, 0);
        //msgctl(msqid_response, IPC_RMID, 0);
        exit(SIGINT);
    }
    if (sig == SIGTERM) {
        printf("Signal SIGTERM\n");
        // Клиенты не должны удалять очередь
        //msgctl(msqid_request, IPC_RMID, 0);
        //msgctl(msqid_response, IPC_RMID, 0);
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

    key_t key_request = ftok(argv[1], 'A');
    if (key_request == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid_request = msgget(key_request, 0)) == -1) {
        perror("msgget");
        exit(1);
    }

    key_t key_response = ftok(argv[1], 'B');
    if (key_response == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msqid_response = msgget(key_response, 0)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Клиенты не должны удалять очередь
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    //sigaction(SIGINT, &act, NULL);
    //sigaction(SIGTERM, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);

    printf("My pid: %d\n", getpid());

    while (1) {
        //strcpy(request.data, argv[2]);
        sleep(delay);

        if (msgrcv(msqid_response, &response, sizeof(request) - 4, getpid(), 0) == -1) {
            if (flag == 0) {
                perror("msgrcv");
                exit(1);
            }
        }

        if (flag == 0) {
            printf("Got response message:\n");
            printf("Response message type: %ld\n", response.type);
            printf("Response message msgInitiator: %ld\n", response.msgInitiator);
            printf("Response message: %s\n", response.data);
        }
        flag = 0;
    }

    // Клиенты не должны удалять очередь
    //msgctl(msqid_request, IPC_RMID, 0);
    //msgctl(msqid_response, IPC_RMID, 0);

    exit(0);
}