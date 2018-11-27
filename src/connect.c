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
#include <signal.h>

void handler(int s) {
  printf("CAUGHT SIGPIPE\n");
}

void startHeartbeatService() {
    //signal(SIGPIPE, handler);

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

void startDisplay() {
    //signal(SIGPIPE, handler);

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
      /*
        char sendline[100];
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);
        write(comm_fd, sendline, strlen(sendline)+1);
      */
    }
}

/*
 * This module should be responsible for maintaining a connection to the socket.
 * It should be capable of:
 * - Waiting for a connection
 * - Holding an active connection
 * - Recovering from a broken connection
 *
 * Use a state machine?
 * States: Inactive, Listening, Connected, Error
 *
 * Message Format:
 * - Header:
 *   - Fixed size: describes size of incoming message
 *   - OPCODE:SIZE
 * - Message:
 *   - Dynamic size: described by header
 *   - MESSAGE:TAG:TAG:...
 */

/*
 * enum ConnectionStatus
 * enum ConnectionOpCode
 * struct Connection
 * struct Message
 *
 * int startConnection(*Connection, settings...)
 * int endConnection(*Connection)
 * int recvMessage(*Connection, *Message)
 *
 * Example Usage:
 *
 * Connection connection;
 * if (startConnection(&connection, 8080) < 0) {
 *   exit;
 * }
 * for (;;) {
 *   if (reasonForExit) {
 *     break;
 *   }
 *   Message message;
 *   if (recvMessage(&connection, &message) < 0) {
 *     break;
 *   }
 *   ... Do things with message.
 * }
 * endConnection(&connection);
 */
