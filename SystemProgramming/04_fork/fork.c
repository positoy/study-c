#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("root process : pid(%d), ppid(%d)\n", getpid(), getppid());

    // fork
    // forked process copies even heap memory on Copy-On-Write policy.
    // So processes doens't share dynamically allocated memory.
    char *p = malloc(1024);
    int ret = fork();

    while (1) {
        sleep(1);
        if (ret == 0)
            printf("child : ret(%d), pid(%d), ppid(%d)\n", ret, getpid(), getppid());
        else
            printf("parent : ret(%d), pid(%d), ppid(%d)\n", ret, getpid(), getppid());
    }

    return;
}


