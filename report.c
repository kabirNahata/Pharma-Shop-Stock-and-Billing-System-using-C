// report.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "structs.h"

#define BILL_FILE "bill.txt"
#define STOCK_FILE "stock.txt"

// Utility: Get today's date in YYYY-MM-DD
void get_today_date(char *buf) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buf, 11, "%Y-%m-%d", t); // 10 chars + null
}

// Convert string to lowercase (for search)
void to_lower(char *str) {
    for (; *str; str++) *str = tolower(*str);
}

void show_today_bills() {
    FILE *file = fopen(BILL_FILE, "r");
    if (!file) {
        printf("No billing history found.\n");
        return;
    }

    char line[256], today[11];
    int found = 0;
    get_today_date(today);

    printf("\n=== Bills for %s ===\n", today);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, today)) found = 1;
        if (found) {
            printf("%s", line);
            if (strcmp(line, "\n") == 0) found = 0; // blank line means next invoice
        }
    }

    fclose(file);
}

void show_current_stock() {
    FILE *file = fopen(STOCK_FILE, "r");
    if (!file) {
        printf("No stock found.\n");
        return;
    }

    Medicine med;
    printf("\n%-5s %-20s %-12s %-12s %-8s %-8s\n", 
        "ID", "Name", "MFG", "EXP", "Price", "Qty");
    printf("---------------------------------------------------------------\n");
    while (fscanf(file, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &med.id, med.name, med.mfg_date, med.exp_date, &med.price, &med.quantity) == 6) {
        printf("%-5d %-20s %-12s %-12s %-8.2f %-8d\n",
               med.id, med.name, med.mfg_date, med.exp_date, med.price, med.quantity);
    }

    fclose(file);
}

void search_medicine() {
    char keyword[50], lower_name[50], lower_key[50];
    printf("Enter medicine name to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    strcpy(lower_key, keyword);
    to_lower(lower_key);

    FILE *file = fopen(STOCK_FILE, "r");
    if (!file) {
        printf("Error: stock.txt not found.\n");
        return;
    }

    Medicine med;
    int found = 0;
    while (fscanf(file, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &med.id, med.name, med.mfg_date, med.exp_date, &med.price, &med.quantity) == 6) {
        strcpy(lower_name, med.name);
        to_lower(lower_name);
        if (strstr(lower_name, lower_key)) {
            if (!found) {
                printf("\nSearch Results:\n");
                printf("%-5s %-20s %-12s %-12s %-8s %-8s\n", 
                    "ID", "Name", "MFG", "EXP", "Price", "Qty");
                printf("---------------------------------------------------------------\n");
            }
            found = 1;
            printf("%-5d %-20s %-12s %-12s %-8.2f %-8d\n",
                   med.id, med.name, med.mfg_date, med.exp_date, med.price, med.quantity);
        }
    }

    if (!found) {
        printf("No matching medicine found.\n");
    }

    fclose(file);
}

void report_menu() {
    int choice;
    do {
        printf("\n=== Reports Menu ===\n");
        printf("1. View Today’s Bills\n");
        printf("2. View Current Stock\n");
        printf("3. Search Medicine by Name\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: show_today_bills(); break;
            case 2: show_current_stock(); break;
            case 3: search_medicine(); break;
            case 4: break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);
}
