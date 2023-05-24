#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "scanner.h"
#include "scanner_internal.h"
#include "read_config.h"
#include "../utils/ip_range.h"
#include <sys/time.h>
#include <fcntl.h> // Added for non-blocking mode
#include <errno.h> // Added for error handling

#define VERBOSE_MODE read_config("CONFIG_VERBOSE_MODE")
#define TIMEOUT_VALUE read_config("CONFIG_TIMEOUT_SEC")

bool scanPort(const char* ipAddress, int port) {
    // Create a socket for the port scan
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return false;
    }

    // Prepare the socket address structure
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
    serverAddress.sin_port = htons(port);

    // Set the socket to non-blocking mode
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    // Attempt to connect to the specified port
    int connectResult = connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    if (connectResult < 0) {
        // Check if the connection is still in progress
        if (VERBOSE_MODE == 2) printf("Connection still in progress with port %d\n",port);
        if (errno == EINPROGRESS) {
            // Define the timeout value for the connection
            struct timeval timeout;
            timeout.tv_sec = TIMEOUT_VALUE;  // second
            timeout.tv_usec = 0; // 0 microseconds

            // Create a file descriptor set to hold the socket
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(sockfd, &fds);

            // Use the select function to check for socket activity
            int selectResult = select(sockfd + 1, NULL, &fds, NULL, &timeout);

            if (selectResult > 0) {
                // The socket is ready for reading, indicating a successful connection
                if (VERBOSE_MODE == 2) printf("Successful connection, the socket is ready for reading\n");
                int socketError;
                socklen_t socketErrorLength = sizeof(socketError);
                getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &socketError, &socketErrorLength);

                if (socketError == 0) {
                    // Connection successful, port is open
                    if (VERBOSE_MODE == 2) printf("Connection successful, port %d is open\n", port);
                    close(sockfd);
                    return true;
                }
            } else if (selectResult == 0) {
                // The select function timed out, indicating a closed port
                if (VERBOSE_MODE == 2) printf("Connection timed out with port %d [timeout config is set to %d sec]\n", port, TIMEOUT_VALUE);
                close(sockfd);
                return false;
            }
        } else {
            // Connection failed, port is closed
            if (VERBOSE_MODE == 2) printf("Connection failed, port is closed\n");
            close(sockfd);
            return false;
        }
    } else {
        // Connection successful, port is open
        if (VERBOSE_MODE == 2) printf("Connection successful, port is open\n");
        close(sockfd);
        return true;
    }

    // Close the socket
    close(sockfd);
    return false;
}

void performScan(const char* ipRange, int startPort, int endPort) {
    if (VERBOSE_MODE == 1 || VERBOSE_MODE == 2) printf("Performing network scan...\n");

    // Parse the IP range
    IPAddressRange range;
    if (!parseIPRange(ipRange, &range)) {
        if (VERBOSE_MODE == 2) printf("Invalid IP address/range: %s\n", ipRange);
        return;
    }

    // Iterate over the IP addresses in the range
    unsigned int startIP = ntohl(range.start); // Convert start IP to host byte order
    unsigned int endIP = ntohl(range.end);     // Convert end IP to host byte order

    for (unsigned int ip = startIP; ip <= endIP; ++ip) {
        struct in_addr addr;
        addr.s_addr = htonl(ip); // Convert IP to network byte order
        char* ipAddress = inet_ntoa(addr);
        printf("Scanning IP: %s\n", ipAddress);
        // Iterate over the ports in the range
        for (int port = startPort; port <= endPort; ++port) {
            if (VERBOSE_MODE == 1 || VERBOSE_MODE == 2) printf("Trying with port: %d\n", port);
            if (scanPort(ipAddress, port)) {
                printf("Port %d open\n", port);
            }
        }
    }

    if (VERBOSE_MODE == 1 || VERBOSE_MODE == 2) printf("Network scan completed.\n");
}
