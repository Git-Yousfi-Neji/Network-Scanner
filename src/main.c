#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "scanner.h"
#include "utils/calculate _numIP.h"

// Structure to hold the arguments for the scan thread
struct ScanThreadArgs {
    char ipRange[100];
    int startPort;
    int endPort;
};

// Function signature for the thread routine
void *scanThread(void *arg) {
    struct ScanThreadArgs *args = (struct ScanThreadArgs *)arg;
    performScan(args->ipRange, args->startPort, args->endPort);
    free(args);  // Free the dynamically allocated argument structure
    pthread_exit(NULL);
}

int main() {
    char ipRange[100];
    int startPort, endPort;

    printf("Enter an IP/range(startIP-endIP) to scan: ");
    scanf("%99s", ipRange);

    printf("Enter IP Start: ");
    scanf("%d", &startPort);

    printf("Enter IP End: ");
    scanf("%d", &endPort);

    // Calculate the number of IP addresses 
    int numIPs = calculateNumIPs(ipRange);

    // Create an array of thread IDs
    pthread_t *threads = (pthread_t *)malloc(numIPs * sizeof(pthread_t));
    if (threads == NULL) {
        perror("Failed to allocate memory for threads");
        return 1;
    }

    // Scan each IP address and port combination in a separate thread
    int threadCount = 0;
    char *token = strtok(ipRange, ",");
    while (token != NULL) {
        struct ScanThreadArgs *args = (struct ScanThreadArgs *)malloc(sizeof(struct ScanThreadArgs));
        if (args == NULL) {
            perror("Failed to allocate memory for thread arguments");
            return 1;
        }

        strncpy(args->ipRange, token, sizeof(args->ipRange) - 1);
        args->startPort = startPort;
        args->endPort = endPort;

        int createResult = pthread_create(&threads[threadCount], NULL, scanThread, (void *)args);
        if (createResult != 0) {
            perror("Failed to create thread");
            return 1;
        }

        token = strtok(NULL, ",");
        threadCount++;
    }

    // Wait for all threads to finish
    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    free(threads);

    printf("Scan Completed.\n");

    return 0;
}
