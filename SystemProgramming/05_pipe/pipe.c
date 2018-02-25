#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END  0
#define WRITE_END 1

#define CHILD_PROCESS (ret == 0)

int main()
{
    int pipefd[2];
    char buffer[15];

    // pipe
    pipe(pipefd);
    printf("pipefd[0] : %d\n", pipefd[0]);
    printf("pipefd[1] : %d\n", pipefd[1]);


    // fork
    int ret = fork();
    if (ret == -1) {
        perror("fork failed.");
        return 1;
    }

    if (CHILD_PROCESS) {
        // child write
        strcpy(buffer, "hello, daddy!\n");
        write(pipefd[WRITE_END], buffer, sizeof(buffer));

        // child read
        printf("PID(%d),PPID(%d) :\n", getpid(),getppid());
        read(pipefd[READ_END], buffer, sizeof(buffer));
        write(STDOUT_FILENO, buffer, sizeof(buffer));
        /*while (read(pipefd[READ_END], buffer, 1) > 0)*/
            /*write(STDOUT_FILENO, buffer, 1);*/

        _exit(EXIT_SUCCESS); // immediately exit closing file descripters
    }

    if(!CHILD_PROCESS) {
        // parent read
        printf("PID(%d),PPID(%d) :\n", getpid(),getppid());
        read(pipefd[READ_END], buffer, sizeof(buffer));
        write(STDOUT_FILENO, buffer, sizeof(buffer));
        /*while (read(pipefd[READ_END], buffer, 1) > 0)*/
            /*write(STDOUT_FILENO, buffer, 1);*/

        // parent write
        strcpy(buffer, "hello, boy!\n");
        write(pipefd[WRITE_END], buffer, sizeof(buffer));

        wait(NULL);         // wait for children to exit
        exit(EXIT_SUCCESS); // exit closing file descripters
    }
}

