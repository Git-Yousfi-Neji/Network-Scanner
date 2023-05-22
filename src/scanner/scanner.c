#include <stdio.h>
#include "scanner.h"
#include "scanner_internal.h"
#include "../utils/ip_range.h"

void performScan(const char* ipRange, int startPort, int endPort) {
    printf("Performing network scan...\n");

    // Parse the IP range
    IPAddressRange range;
    if (!parseIPRange(ipRange, &range)) {
        printf("Invalid IP range: %s\n", ipRange);
        return;
    }

    // Iterate over the IP addresses in the range
    for (unsigned int ip = range.start; ip <= range.end; ++ip) {
        printf("Scanning IP: %u.%u.%u.%u\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

        // Iterate over the ports in the range
        for (int port = startPort; port <= endPort; ++port) {
            if (scanPort(ip, port)) {
                printf("Port %d open\n", port);
            }
        }
    }

    printf("Network scan completed.\n");
}
