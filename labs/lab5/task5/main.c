#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


// Просмотр запущенных очередей сообщений:
// ipcs -a
// ./task5 1
// ipcs -a
// Удалить очередь:
// ipcrm -q 12
// 12 - msqid
// Можно написать программу, осуществляющую exec: ipcrm -q 12
int main(int argc, char *argv[], char *envp[]) {
    key_t key;
    int msqid, msgtype, k;
    char *p;
    struct message *m;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s msqid\n", argv[0]);
        exit(1);
    }
    msqid = strtol(argv[1], &p, 10);
    if (argv[1] == p || *p) {
        fprintf(stderr, "Value msqid %s is not valid\n", argv[1]);
        exit(1);
    }

    if (msgctl(msqid, IPC_RMID, 0)) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    exit(0);
}
