#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main() {
    char ipRange[20];

    printf("Enter IP range to scan: ");
    scanf("%19s", ipRange);

    performScan(ipRange);
    printf("Scan Completed.");

    return 0;
}
