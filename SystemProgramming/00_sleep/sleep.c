#include <unistd.h>
#include <time.h>

int main()
{
    int repeat = 3;
    while (repeat--) {
        puts("sleep(1) sleeps for a second.");
        sleep(1);
    }

    repeat = 3;
    while (repeat--) {
        puts("usleep(1000000) sleeps for a second.");
        usleep(1000000);
    }

    repeat = 3;
    while (repeat--) {
        puts("nanosleep(struct timespec* , NULL) sleeps for nano seconds");
        struct timespec ts = {1, 0}; // seconds, nanoseconds
        nanosleep(&ts, NULL);
    }

    return;
}
