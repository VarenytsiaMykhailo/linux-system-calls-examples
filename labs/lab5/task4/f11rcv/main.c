#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long type;
    char text[1];
};

// Просмотр запущенных очередей сообщений:
// ipcs -a
// ./f11rcv 0 9
int main(int argc, char *argv[], char *envp[]) {
    key_t key;
    int msqid, msgtype, k;
    char *p;
    struct message *m;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s msqid msgtype\n", argv[0]);
        exit(1);
    }
    msqid = strtol(argv[1], &p, 10);
    if (argv[1] == p || *p) {
        fprintf(stderr, "Value msqid %s is not valid\n", argv[1]);
        exit(1);
    }
    msgtype = strtol(argv[2], &p, 10);
    if (argv[2] == p || *p) {
        fprintf(stderr, "Value msgtype %s is not valid\n", argv[2]);
        exit(1);
    }
    if ((m = malloc(7)) == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    // 4 байта уйдут на message->type
    if ((k = msgrcv(msqid, m, 3, msgtype, MSG_NOERROR | IPC_NOWAIT)) == -1) {
        perror("msgrcv");
        free(m);
        exit(1);
    }
    printf("Type = %d\n", m->type);
    printf("%*s\n", k, m->text);
    free(m);
    exit(0);
}
