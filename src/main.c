#include <stdio.h>
#include "scanner.h"

int main() {
    //char ipRange[100];
    int startPort=1;
    int endPort=445;

    //printf("Enter IP range to scan: ");
    //scanf("%26s", ipRange);
    /*
    printf("Enter IP Start: ");
    scanf("%d", &startPort);
    
    printf("Enter IP End: ");
    scanf("%d", &endPort);
    */
    performScan("192.168.1.1-192.168.1.3", startPort, endPort);
    printf("Scan Completed.\n");

    return 0;
}
