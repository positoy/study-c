#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

/****************
 * Socket Client
 ****************

 TWO STEPS

 1. socket
 2. connect

 ****************/

int main()
{
    /* socket client */
    
    // creat socket
    int sock_fd;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("failed to create socket.");
        return -1;
    }

    // server information data structure
    struct sockaddr_in address;
    memset(&address, 0x00, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        perror("failed to convert ip address.\n");
        return -1;
    }

    // connect
    socklen_t addrlen;
    if (connect(sock_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("failed to connect.\n");
        return -1;
    }
    
    // read & send
    char buffer[2048];
    int cnt;
    while ((cnt = read(sock_fd, buffer, 1)) > 0) {
        write(STDOUT_FILENO, buffer, 1);
        printf("(%d)", cnt);
    }

    strcpy(buffer, "hello! I'm a client.\n");
    send(sock_fd, buffer, strlen(buffer), 0);

    close(sock_fd);
    return 0;
}
