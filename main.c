#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
    char ipRange[20];
    int startPort, endPort;

    printf("Enter IP range to scan: ");
    scanf("%19s", ipRange);
    
    printf("Enter IP Start: ");
    scanf("%d", &startPort);
    
    printf("Enter IP End: ");
    scanf("%d", &endPort);

    performScan(ipRange, startPort, endPort);
    printf("Scan Completed.\n");

    return 0;
}
