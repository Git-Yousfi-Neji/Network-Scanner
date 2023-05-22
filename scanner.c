#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "scanner.h"

void performScan(const char* ipRange, int startPort, int endPort) {
    // Iterate over the specified port range
    for (int port = startPort; port <= endPort; ++port) {
        // Create a socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Socket creation failed");
            continue;
        }

        // Prepare the server address structure
        struct sockaddr_in server;
        server.sin_family = AF_INET;

        // Iterate over the IP addresses in the range
        char ip[16];  // Buffer to store the current IP address
        strncpy(ip, ipRange, sizeof(ip));
        char* hyphen = strchr(ip, '-');
        if (hyphen != NULL) {
            *hyphen = '\0';
        }

        struct in_addr addr;
        if (inet_pton(AF_INET, ip, &addr) != 1) {
            perror("Invalid IP address");
            close(sock);
            continue;
        }
        

        // Scan the IP range
        for (uint32_t i = ntohl(addr.s_addr); i <= ntohl(server.sin_addr.s_addr); ++i) {
            server.sin_addr.s_addr = htonl(i);

            // Set the port number
            server.sin_port = htons(port);

            // Attempt to connect to the IP address and port
            if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0) {
                // Connection successful, port is open
                printf("Open port found on %s:%d\n", inet_ntoa(server.sin_addr), port);
            }
        }

        // Close the socket
        close(sock);
    }
}