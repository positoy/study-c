#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

/****************
 * Socket Server
 ****************

 FOUR STEPS

 1. socket
 2. bind
 3. listen
 4. accept

 ****************/

int main()
{
    int cnt_client = 0;

    printf("server parent : pid(%d), ppid(%d)\n", getpid(), getppid());
    /* socket server */
    
    // create socket
    // internet domain(AF_INET), TCP(SOCK_STREAM) ; UDP(SOCK_DATAGRAM)
    int sock_fd;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("failed to create socket.\n");
        return -1;
    }

    // bind
    // Internet address (AF_INET), Ip address(INADDR_ANY) mapped to localhost(127.0.0.1)
    // PORT with byte ordering(HTONS)
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(sock_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("failed to bind.\n");
        return -1;
    }

    // listen
    if (listen(sock_fd, 4) < 0) {
        perror("failed to listen.\n");
        return -1;
    }

    // new socket
    while (1) {
        socklen_t addrlen;
        int new_socket;
        if ((new_socket = accept(sock_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("failed to accept.\n");
            return -1;
        }

        int ret;
        if ((ret = fork()) == 0) {
            printf("server child : pid(%d), ppid(%d) --- new connection (%d:%d)\n", getpid(), getppid(), address.sin_addr.s_addr, address.sin_port);

            char buffer[2048];
            strcpy(buffer, "you are connected!\n");
            send(new_socket, buffer, strlen(buffer), 0);

            sprintf(buffer, "there are %d clients connected.\n", ++cnt_client);
            send(new_socket, buffer, strlen(buffer), 0);

            int cnt;
            while ((cnt = read(new_socket, buffer, 1)) > 0) {
                write(STDOUT_FILENO, buffer, 1);
                printf("(%d)", cnt);
            }
        }
    }
    
}

