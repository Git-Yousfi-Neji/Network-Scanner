
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "read_config.h"

#define CONFIG_FILE "config.cfg"
#define MAX_LINE_LENGTH 100

int read_config(const char* conf) {
    FILE* file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening config file: %s\n", CONFIG_FILE);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    char token[50];
    int value;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^=]=%d", token, &value) == 2) {
            if (strcmp(token, conf) == 0) {
                fclose(file);
                return value;
            }
        }
    }

    fclose(file);
    fprintf(stderr, "Token not found in config file: %s\n", conf);
    return -1;
}