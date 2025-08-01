// pharma.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define INFO_FILE "pharma_info.txt"

// Check if info file exists and has valid data
int pharma_info_exists() {
    FILE *file = fopen(INFO_FILE, "r");
    if (!file) return 0;

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) > 1) count++;
    }
    fclose(file);
    return (count >= 2); // name + address required
}

void input_pharma_info() {
    FILE *file = fopen(INFO_FILE, "w");
    if (!file) {
        printf("Error: Unable to open pharma_info.txt\n");
        return;
    }

    PharmaInfo info;

    printf("\n=== Enter Pharma Shop Info ===\n");

    printf("Shop Name: ");
    fgets(info.name, sizeof(info.name), stdin);
    info.name[strcspn(info.name, "\n")] = '\0';

    printf("Address: ");
    fgets(info.address, sizeof(info.address), stdin);
    info.address[strcspn(info.address, "\n")] = '\0';

    printf("ASCII Logo (optional, press Enter to skip): ");
    fgets(info.logo, sizeof(info.logo), stdin);
    info.logo[strcspn(info.logo, "\n")] = '\0';

    fprintf(file, "%s\n%s\n%s\n", info.name, info.address, info.logo);
    fclose(file);

    printf("Shop info saved successfully.\n");
}

void display_pharma_info() {
    FILE *file = fopen(INFO_FILE, "r");
    if (!file) {
        printf("Error: Could not open pharma_info.txt\n");
        return;
    }

    PharmaInfo info = {"", "", ""};
    fgets(info.name, sizeof(info.name), file);
    fgets(info.address, sizeof(info.address), file);
    fgets(info.logo, sizeof(info.logo), file);

    // Strip newlines
    info.name[strcspn(info.name, "\n")] = '\0';
    info.address[strcspn(info.address, "\n")] = '\0';
    info.logo[strcspn(info.logo, "\n")] = '\0';

    printf("\n=============================\n");
    if (strlen(info.logo) > 0) {
        printf("%s\n", info.logo);
    }
    printf("%s\nAddress: %s\n", info.name, info.address);
    printf("=============================\n");

    fclose(file);
}

// Fetch info into provided buffers (for billing use)
void get_pharma_info(char *name, char *address, char *logo) {
    FILE *file = fopen(INFO_FILE, "r");
    if (!file) {
        strcpy(name, "Pharma Shop");
        strcpy(address, "N/A");
        strcpy(logo, "");
        return;
    }

    fgets(name, 100, file);
    fgets(address, 200, file);
    fgets(logo, 1000, file);
    
    // Strip newlines
    name[strcspn(name, "\n")] = '\0';
    address[strcspn(address, "\n")] = '\0';
    logo[strcspn(logo, "\n")] = '\0';

    fclose(file);
}
