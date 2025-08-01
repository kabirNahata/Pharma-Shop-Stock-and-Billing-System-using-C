// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "pharma.h"
#include "stock.h"
#include "billing.h"
#include "logs.h"
#include "structs.h"
#include "report.h"

int main() {
    if (!login()) {
        printf("Login failed 3 times. Exiting...\n");
        return 1;
    }

    if (!pharma_info_exists()) {
        input_pharma_info();
    }

    int choice;
    do {
        printf("\n========== Pharma Shop Menu ==========\n");
        printf("1. Manage Medicine Stock\n");
        printf("2. Process Billing\n");
        printf("3. View Pharma Info\n");
        printf("4. Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                stock_menu();
                break;
            case 2:
                billing_menu();
                break;
            case 3:
                display_pharma_info();
                break;
            case 4:
                report_menu();
                break;
            case 5:
                printf("Exiting... Thank you!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
