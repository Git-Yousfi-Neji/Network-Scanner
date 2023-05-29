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
#include "port_specific_scanner.h"
#include <sys/time.h>
#include <fcntl.h> // Added for non-blocking mode
#include <errno.h> // Added for error handling

#define VERBOSE_MODE read_config("CONFIG_VERBOSE_MODE")

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
            /*if (scanPort(ipAddress, port)) {
                printf("Port %d open\n", port);
            }*/
            scanUDPPort(ip, port);
            scanTCPPort(ip, port);
        }
    }

    printf("Network scan completed.\n");
}
