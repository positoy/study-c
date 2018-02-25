#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "shmtest.h"

int main()
{
    /*int shmid = shmget(TEST_SHMID, TEST_SHMSIZE, IPC_CREAT|0666);*/
    /*if (shmid < 0) {*/
        /*perror("failed to create shared memory");*/
        /*return -1;*/
    /*}*/


    /*char *memory;*/
    /*if ((memory = shmat(TEST_SHMID, NULL, 0)) < 0) {*/
        /*perror("failed to attach.\n");*/
        /*return -1;*/
    /*}*/

    /*memset(memory, 0x00, TEST_SHMSIZE);*/

    int ret = fork();
    int ret2 = fork();


    if (ret == 0) {
        if (ret2 == 0) {
            printf("ret(%d), getpid(%d), getppid(%d), ret(%d:%d)\n", getpid(), getppid(), ret,ret2);
        }
        else {
            printf("ret(%d), getpid(%d), getppid(%d), ret(%d:%d)\n", getpid(), getppid(), ret,ret2);
        }
    }
    else {
        if (ret2 == 0) {
            printf("ret(%d), getpid(%d), getppid(%d), ret(%d:%d)\n", getpid(), getppid(), ret,ret2);
        }ß
        else {
            printf("ret(%d), getpid(%d), getppid(%d), ret(%d:%d)\n", getpid(), getppid(), ret,ret2);
        }
    }



}
