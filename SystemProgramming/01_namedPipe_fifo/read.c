#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main()
{
    int fd, retval;
    char buffer[100] = "";

    // open
    fd = open(FIFO_PATH, O_RDONLY);
    // read
    while (1) {
        retval = read(fd, buffer, sizeof(buffer));
        if (strcmp(buffer, "eof") == 0) {
            close(fd);
            return 0;
        }
        puts(buffer);
    }
    close(fd);
    return 0;
}
