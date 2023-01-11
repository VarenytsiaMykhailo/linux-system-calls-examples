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
int main(int argc, char *argv[], char *envp[]) {
    key_t key;
    int msqid, msgtype, k;
    char *p;
    struct message *m;
    if (argc != 4) {
        fprintf(stderr, "Usage: %s msqid msgtype message\n", argv[0]);
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
    k = strlen(argv[3]);
    if ((m = malloc(k + 5)) == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    m->type = msgtype;
    if (k) {
        strcpy(m->text, argv[3]);
    }
    if (msgsnd(msqid, m, k, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    free(m);
    exit(0);
}
