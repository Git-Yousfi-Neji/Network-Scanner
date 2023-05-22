#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "scanner.h"

void performScan(const char* ipRange) {
    struct sockaddr_in server;
    int sock;
    int port;
    int result;

    for (port = 1; port <= 65535; ++port) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        if (inet_pton(AF_INET, ipRange, &(server.sin_addr)) <= 0) {
            perror("inet_pton");
            exit(EXIT_FAILURE);
        }

        result = connect(sock, (struct sockaddr*)&server, sizeof(server));
        if (result == 0) {
            printf("Port %d is open\n", port);
        }

        close(sock);
    }
}
