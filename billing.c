// billing.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "login.h"
#include "logs.h"
#include "pharma.h"

#define STOCK_FILE "stock.txt"
#define BILL_FILE "bill.txt"

typedef struct {
    Medicine med;
    int quantity;
} BillItem;

void billing_menu() {
    FILE *stock = fopen(STOCK_FILE, "r");
    if (!stock) {
        printf("Error: Stock file not found.\n");
        return;
    }

    // Load all available stock
    Medicine all_meds[100];
    int med_count = 0;
    while (fscanf(stock, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &all_meds[med_count].id,
           all_meds[med_count].name,
           all_meds[med_count].mfg_date,
           all_meds[med_count].exp_date,
           &all_meds[med_count].price,
           &all_meds[med_count].quantity) == 6) {
        med_count++;
    }
    fclose(stock);

    // Display stock
    printf("\n--- Available Medicines ---\n");
    printf("%-5s %-20s %-8s %-8s\n", "ID", "Name", "Price", "Qty");
    for (int i = 0; i < med_count; i++) {
        printf("%-5d %-20s %-8.2f %-8d\n", 
            all_meds[i].id, all_meds[i].name, all_meds[i].price, all_meds[i].quantity);
    }

    // Input order
    BillItem items[50];
    int item_count = 0;
    char more = 'y';
    while (more == 'y' || more == 'Y') {
        int id, qty;
        printf("Enter medicine ID to buy: ");
        scanf("%d", &id);
        printf("Enter quantity: ");
        scanf("%d", &qty);
        getchar();

        int found = 0;
        for (int i = 0; i < med_count; i++) {
            if (all_meds[i].id == id) {
                if (qty > all_meds[i].quantity) {
                    printf("Not enough stock for %s\n", all_meds[i].name);
                    found = 1;
                    break;
                }
                items[item_count].med = all_meds[i];
                items[item_count].quantity = qty;
                item_count++;
                all_meds[i].quantity -= qty;
                found = 1;
                break;
            }
        }

        if (!found) printf("Medicine not found.\n");

        printf("Add more items? (y/n): ");
        scanf("%c", &more);
        getchar();
    }

    if (item_count == 0) {
        printf("No items purchased.\n");
        return;
    }

    // Update stock
    FILE *temp = fopen("temp_stock.txt", "w");
    for (int i = 0; i < med_count; i++) {
        fprintf(temp, "%d,%s,%s,%s,%.2f,%d\n",
            all_meds[i].id, all_meds[i].name, all_meds[i].mfg_date,
            all_meds[i].exp_date, all_meds[i].price, all_meds[i].quantity);
    }
    fclose(temp);
    remove(STOCK_FILE);
    rename("temp_stock.txt", STOCK_FILE);

    // Prepare bill
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    int invoice_no = rand() % 9000 + 1000; // dummy invoice no
    const char *user = get_logged_in_user();
    char shop_name[100], address[200], logo[1000];
    get_pharma_info(shop_name, address, logo);

    float total = 0.0;
    FILE *bill = fopen(BILL_FILE, "a");
    if (!bill) {
        printf("Could not write to bill.txt\n");
        return;
    }

    // Console Bill Header
    printf("\n*********************************************\n");
    if (strlen(logo) > 0) printf("%s\n", logo);
    printf("%s\nAddress: %s\n", shop_name, address);
    printf("*********************************************\n");
    printf("Invoice No: %d     Date: %s\n", invoice_no, date);
    printf("Served By: %s\n", user);
    printf("Items:\n");

    fprintf(bill, "Invoice No: %d | Date: %s | User: %s\n", invoice_no, date, user);

    for (int i = 0; i < item_count; i++) {
        float subtotal = items[i].quantity * items[i].med.price;
        total += subtotal;
        printf("%d. %s x%d = %.2f\n", i+1, items[i].med.name, items[i].quantity, subtotal);
        fprintf(bill, "%s x%d = %.2f\n", items[i].med.name, items[i].quantity, subtotal);
    }

    printf("Total: %.2f\n", total);
    printf("*********************************************\n");
    printf("Thank you! Stay Healthy\n");
    printf("*********************************************\n\n");

    fprintf(bill, "Total = %.2f\n\n", total);
    fclose(bill);

    // Log action
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "processed a bill worth %.2f", total);
    write_log(user, log_msg);
}
