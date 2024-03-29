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
// В этой программе будет сгенерирована ошибка и очередь сообщений не удалится. Нужно удалить вручную с помощью команды:
// ipcrm -q 12
// 12 - msqid
int main(int argc, char *argv[], char *envp[]) {
    key_t key;
    int msqid, k, i;
    struct message *m1, *m2;
    // ftok - генерирует ключ
    if ((key = ftok(argv[0], 'A')) == -1) {
        perror(argv[0]);
        exit(1);
    }
    // Получаем доступ к существующей очереди по ключу или создаем новую, если очереди не существует
    if ((msqid = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }
    // Формируем сообщение
    m1 = malloc(14);
    //m1->type = 1;
    strcpy(m1->text, "123456789"); // 10 байт т.к. \0

    for (i = 10; i > 0; i--) {
        m1->type = i;
        // Отправляем сообщение. Размер указываем 9 т.к. \0 не учитывается
        if (msgsnd(msqid, m1, 9, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }
    free(m1);

    /*
    m2 = malloc(14);
    m2->type = 0;
    strcpy(m2->text, "aaaaaaaaa"); // 10 байт т.к. \0
    // msgtype 0 - считать первое сообщение из очереди, 1...n - сообщение с определенным типом
    // NSG_EXCEPT - любого типа, кроме msgtyp. Указали 10, следующий будет 9ый по принципу FIFO
    if ((k = msgrcv(msqid, m2, 3, 10, 0)) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("k=%d\n", k);
    printf("m2->type=%ld, m2->text='%s'\n", m2->type, m2->text);
    free(m2);
     */
    //msgctl(msqid, IPC_RMID, 0); // Удаляем очередь сообщений
    exit(0);
}
