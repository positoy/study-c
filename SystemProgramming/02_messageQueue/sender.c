#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char msgtxt[100];
};

int main() {
    struct msgbuf msg;
    int msgid;
    key_t key;

    // get message key
    if ((key = ftok("sender.c", 'b')) == -1) {
        perror("key");
        exit(1);
    }

    // get message id
    if ((msgid = msgget(key, 0644|IPC_CREAT)) == -1) {
        perror("msgid");
        exit(1);
    }
    printf("\n the msgid is %d", msgid);

    // send message
    msg.mtype = 1;
    while (gets(msg.msgtxt), !feof(stdin)) {
        if (msgsnd(msgid, &msg, sizeof(msg),0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    // delete msgid
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
