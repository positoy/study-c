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

    // rcv message
    for ( ; ; ) {
        if (msgrcv(msgid, &msg, sizeof(msg), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("%s\n", msg.msgtxt);
    }

    return 0;
}
