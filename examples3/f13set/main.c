#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

// Меняем у очереди права доступа
// Просмотр запущенных очередей сообщений:
// ipcs -a
// ./f13set 0 0666
// ipcs -a
// ./f13set 0 0600
// ipcs -a
int main(int argc, char *argv[], char *envp[]) {
    int msqid, rights;
    struct msqid_ds m;
    struct passwd *p;
    struct group *g;
    char *pp;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s msqid rights\n", argv[0]);
        exit(1);
    }
    msqid = strtol(argv[1], &pp, 10);
    if (argv[1] == pp || *pp) {
        fprintf(stderr, "Value msqid %s is not valid\n", argv[1]);
        exit(1);
    }
    rights = strtol(argv[2], &pp, 0); // base 0 выберет сам систему счисления
    if (argv[2] == pp || *pp) {
        fprintf(stderr, "Value rights %s is not valid\n", argv[2]);
        exit(1);
    }
    m.msg_perm.mode = rights;
    m.msg_perm.uid = getuid();
    m.msg_perm.gid = getgid();
    m.msg_qbytes = 16384;

    if (msgctl(msqid, IPC_SET, &m) == -1) {
        perror("msgctl");
        exit(1);
    }

    exit(0);
}
