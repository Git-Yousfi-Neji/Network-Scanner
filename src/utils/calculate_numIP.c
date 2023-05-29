#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "calculate _numIP.h"

int calculateNumIPs(const char *ipRange) {
    char rangeCopy[100];
    strncpy(rangeCopy, ipRange, sizeof(rangeCopy));

    int numIPs = 0;
    char *token = strtok(rangeCopy, ",");
    while (token != NULL) {
        char *dash = strchr(token, '-');
        if (dash != NULL) {
            *dash = '\0';

            struct in_addr startAddr, endAddr;
            if (inet_pton(AF_INET, token, &(startAddr.s_addr)) == 1 &&
                inet_pton(AF_INET, dash + 1, &(endAddr.s_addr)) == 1) {
                uint32_t startIP = ntohl(startAddr.s_addr);
                uint32_t endIP = ntohl(endAddr.s_addr);
                numIPs += (endIP - startIP + 1);
            }
        } else {
            numIPs++;
        }

        token = strtok(NULL, ",");
    }

    return numIPs;
}
