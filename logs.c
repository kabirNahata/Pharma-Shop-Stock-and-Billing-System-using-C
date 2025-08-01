// logs.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "logs.h"

#define LOG_FILE "logs.txt"

void write_log(const char *username, const char *action) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        printf("Error: Could not open logs.txt\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    fprintf(log, "[%s] User: %s %s\n", timestamp, username, action);
    fclose(log);
}

// Optional viewer for reports/debugging
void view_logs() {
    FILE *log = fopen(LOG_FILE, "r");
    if (!log) {
        printf("No logs available.\n");
        return;
    }

    char line[256];
    printf("\n=== System Logs ===\n");
    while (fgets(line, sizeof(line), log)) {
        printf("%s", line);
    }
    fclose(log);
}
