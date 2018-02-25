#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid1, pid2;
    int status;

    // by forking twice and let child to terminate, we can create daemon process.
    if (pid1 = fork()) {
        waitpid(pid1, &status, NULL);
    }
    else if (!pid1) {
        if (pid2 = fork()) {
            // use exit. return sometimes stop forking
            exit(0);
        }
        else if (!pid2) {
            while(1) {
                sleep(1);
                puts("do something");
            }
        }
        else {
            perror("error occured");
            return -1;
        }
    }
    else {
        perror("error occured");
        return -1;
    }

    return;
}

    
