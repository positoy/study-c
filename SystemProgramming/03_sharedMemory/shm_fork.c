#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define TEST_SHMID 99232
#define TEST_SHMSIZE 1024

int main()
{
    int pid[3], shmid;
    char* memory;

    if ((shmid = shmget(TEST_SHMID, TEST_SHMSIZE, IPC_CREAT|0666)) < 0) {
        perror("shmget failed.\n");
        return -1;
    }

    printf("parent pid(%d), ppid(%d)\n", getpid(), getppid());

    for (int i=0; i<3; i++) {
        printf("fork %d process.\n", i);
        if ((pid[i] = fork()) < 0) {
            perror("failed to fork");
            return -1;
        }
        else if (pid[i] == 0) {
            switch (i)
            {
                case 0:
                    printf("reader pid(%d), ppid(%d)\n", getpid(), getppid());
                    if ((memory = shmat(shmid, NULL, 0)) < 0) {
                        perror("process reader failed to shmat.\n");
                        return -1;
                    }
                    while(1) {
                        sleep(1);
                        printf("(reader) %s\n", memory);
                    }
                    break;
                case 1:
                    printf("writer1 pid(%d), ppid(%d)\n", getpid(), getppid());
                    if ((memory = shmat(shmid, NULL, 0)) < 0) {
                        perror("process writer1 failed to shmat.\n");
                        return -1;
                    }
                    while (1) {
                        sleep(1);
                        char* p = strcpy(memory, "written by writer1");
                        printf("(writer1) %p\n", p);
                    }
                    break;
                case 2:
                    printf("writer2 pid(%d), ppid(%d)\n", getpid(), getppid());
                    if ((memory = shmat(shmid, NULL, 0)) < 0) {
                        perror("process writer2 failed to shmat.\n");
                        return -1;
                    }
                    while(1) {
                        sleep(1);
                        char* p = strcpy(memory, "written by writer2");
                        printf("(writer2) %p\n", p);
                    }
                    break;
            }
        }
    }

    int retpid, status;
    for (int i=0; i<3; i++) {
        retpid = wait(&status);
        printf("%d : process(%d) is just returned. (%s)\n", getpid(), retpid, strerror(errno));

        if (WIFEXITED(status)) puts("wifiexited");
        if (WEXITSTATUS(status)) puts("wexitstatus");
        if (WIFSIGNALED(status)) printf("wifisignaled (%d)\n",WTERMSIG(status));
        if (WCOREDUMP(status)) puts("wcoredump");
        if (WIFSTOPPED(status)) puts("wifstopped");
        if (WSTOPSIG(status)) puts("wstopsig");
        if (WIFCONTINUED(status)) puts("wifcontinued");
    }
}

