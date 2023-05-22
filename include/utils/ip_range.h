#ifndef IP_RANGE_H
#define IP_RANGE_H

#include <stdbool.h>

// Structure to represent an IP address range
typedef struct {
    unsigned int start;
    unsigned int end;
} IPAddressRange;

// Function to parse an IP address range string
bool parseIPRange(const char* ipRange, IPAddressRange* range);

#endif /* IP_RANGE_H */
