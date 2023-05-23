#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "ip_range.h"
#include <arpa/inet.h>

bool parseIPRange(const char* ipRange, IPAddressRange* range) {
    char* rangeCopy = strdup(ipRange);
    char* dashPos = strchr(rangeCopy, '-');

    if (dashPos == NULL) {
        free(rangeCopy);
        return false;
    }

    *dashPos = '\0';

    if (inet_pton(AF_INET, rangeCopy, &(range->start)) <= 0) {
        free(rangeCopy);
        return false;
    }

    if (inet_pton(AF_INET, dashPos + 1, &(range->end)) <= 0) {
        free(rangeCopy);
        return false;
    }

    free(rangeCopy);
    return true;
}
