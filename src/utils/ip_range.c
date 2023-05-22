#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "ip_range.h"
#include <arpa/inet.h>

bool parseIPRange(const char* ipRange, IPAddressRange* range) {
    // Split the IP range into start and end addresses
    char* rangeCopy = strdup(ipRange);
    char* dashPos = strchr(rangeCopy, '-');
    if (dashPos == NULL) {
        free(rangeCopy);
        return false;
    }

    *dashPos = '\0';
    char* startIPStr = rangeCopy;
    char* endIPStr = dashPos + 1;

    // Parse the start and end addresses
    uint32_t startIP = 0;
    uint32_t endIP = 0;

    if (inet_pton(AF_INET, startIPStr, &(struct in_addr){&startIP}) <= 0 ||
        inet_pton(AF_INET, endIPStr, &(struct in_addr){&endIP}) <= 0) {
        free(rangeCopy);
        return false;
    }

    free(rangeCopy);

    // Set the IP range
    range->start = startIP;
    range->end = endIP;

    return true;
}
