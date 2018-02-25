#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

int main()
{
    // init
    int shmid = shmget((key_t)123456789, 6, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("the creation has gone as a failure.\n");
        shmid = shmget((key_t)123456789, 6, 0666);
    }
    printf("we are getting the shared memory created : %d\n", shmid);

    // attachment to shared memory
    void *memory = NULL;
    memory = shmat(shmid, NULL, 0);
    if (memory == NULL) {
        printf("attachment failure.\n");
        return 0;
    }

    // read
    char *p = (char*)memory;
    printf("message is : %s\n", p);

    // dettachment
    int retval = shmdt(p);
    if (retval < 0) {
        printf("suffered dettachment.\n");
        return 0;
    }
    retval = shmctl(shmid, IPC_RMID, NULL);
}
