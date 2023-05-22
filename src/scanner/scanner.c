#include <stdio.h>
#include "scanner.h"
#include "scanner_internal.h"
#include "../utils/ip_range.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


bool scanPorts(unsigned int ipAddress, int port) {
    // Create a socket for the port scan
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return false;
    }

    // Prepare the socket address structure
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(ipAddress);
    serverAddress.sin_port = htons(port);

    // Attempt to connect to the specified port
    int connectResult = connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectResult < 0) {
        // Connection failed, port is closed
        close(sockfd);
        return false;
    }

    // Connection successful, port is open
    close(sockfd);
    return true;
} 






void performScan(const char* ipRange, int startPort, int endPort) {
    printf("Performing network scan...\n");

    // Parse the IP range
    IPAddressRange range;
    if (!parseIPRange(ipRange, &range)) {
        printf("Invalid IP range: %s\n", ipRange);
        return;
    }

    // Iterate over the IP addresses in the range
    unsigned int startIP = ntohl(range.start); // Convert start IP to host byte order
    unsigned int endIP = ntohl(range.end);     // Convert end IP to host byte order

    for (unsigned int ip = startIP; ip <= endIP; ++ip) {
        unsigned int currIP = htonl(ip); // Convert IP to network byte order
        printf("Scanning IP: %u.%u.%u.%u\n", currIP & 0xFF, (currIP >>8) & 0xFF, (currIP >> 16) & 0xFF, (currIP >> 24) & 0xFF);
        // Iterate over the ports in the range
        for (int port = startPort; port <= endPort; ++port) {
            if (scanPorts(currIP, port)) {
                printf("Trying with port: %d\n", port) ;
                printf("Port %d open\n", port);
            }
        }
    }

    printf("Network scan completed.\n");
}
 