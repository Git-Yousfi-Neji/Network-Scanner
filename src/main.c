#include <stdio.h>
#include "scanner.h"

int main() {
    char ipRange[100];
    int startPort=79, endPort=81;

    printf("Enter IP range to scan: ");
    //scanf("%26s", ipRange);
    /*
    printf("Enter IP Start: ");
    scanf("%d", &startPort);
    
    printf("Enter IP End: ");
    scanf("%d", &endPort);
    */
    printf("ip=%s\n", ipRange) ;
    performScan("192.168.1.1-192.168.1.2", startPort, endPort);
    printf("Scan Completed.\n");

    return 0;
}
