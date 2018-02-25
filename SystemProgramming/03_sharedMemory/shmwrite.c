#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main()
{
    // init
    int shmid = shmget((key_t)123456789, 6, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("\nthe creation has gone as a failure.");
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

    // write
    char *p = (char*)memory;
    memset(p, 0x00, 6);
    memcpy(p, "hello", 6);

    // dettachment
    int retval = shmdt(p);
    if (retval < 0) {
        printf("suffered dettachment.\n");
        return 0;
    }
}
