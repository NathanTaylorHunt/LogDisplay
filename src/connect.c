#include "connect.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

void loop() {
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // TODO: Change port

    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));
   
    printf("Waiting for connection...\n");
    bool connected = false;
    while (!connected) {
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            sleep(1);
        } else {
            connected = true;
        }
    }
    
    while (1) {
        char recvline[100];
        read(sockfd, recvline, 100);
        printf("LOG: %s\n", recvline);
    }
}

void server() {
    int listen_fd, comm_fd;
    struct sockaddr_in server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listen_fd, 10);
    printf("Listening...\n");
    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    printf("Accepted\n");
    while (1) {
        char sendline[100];
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);
        write(comm_fd, sendline, strlen(sendline)+1);
    }
}
