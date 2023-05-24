#include <stdio.h>
#include "scanner.h"

int main() {
    char ipRange[100];
    int startPort, endPort;

    printf("Enter an IP/range(startIP-endIP) to scan: ");
    scanf("%26s", ipRange);
    
    printf("Enter IP Start: ");
    scanf("%d", &startPort);
    
    printf("Enter IP End: ");
    scanf("%d", &endPort);

    performScan(ipRange, startPort, endPort);
    printf("Scan Completed.\n");

    return 0;
}
