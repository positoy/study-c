#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main()
{
    int fd;
    char buffer[100] = "";

    // mkfifo
    if (mkfifo(FIFO_PATH, 0666) != 0) {
        perror("failed to make fifo.\n");
        return 1;
    }
    // open
    fd = open(FIFO_PATH, O_WRONLY);
    // write
    while (1) {
        fflush(stdin);
        scanf("%s", buffer);
        if (strcmp(buffer,"end") == 0) {
            write(fd, "eof", 4);
            close(fd);
            return 0;
        }
        // write
        write(fd, buffer, sizeof(buffer));
    }
    close(fd);
    return 0;
}
