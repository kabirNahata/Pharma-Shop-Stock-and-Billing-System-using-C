// stock.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "logs.h"       // if using log_action()
#include "structs.h"
#include "login.h"

#define STOCK_FILE "stock.txt"

void stock_menu() {
    int choice;
    do {
        printf("\n--- Medicine Stock Menu ---\n");
        printf("1. Add New Medicine\n");
        printf("2. Update Medicine Quantity\n");
        printf("3. Delete a Medicine\n");
        printf("4. View All Medicines\n");
        printf("5. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: add_medicine(); break;
            case 2: update_medicine(); break;
            case 3: delete_medicine(); break;
            case 4: view_medicines(); break;
            case 5: break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

// Generate next medicine ID
int get_next_id() {
    FILE *file = fopen(STOCK_FILE, "r");
    if (!file) return 1;

    Medicine med;
    int max_id = 0;
    while (fscanf(file, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &med.id, med.name, med.mfg_date, med.exp_date, &med.price, &med.quantity) == 6) {
        if (med.id > max_id) max_id = med.id;
    }
    fclose(file);
    return max_id + 1;
}

void add_medicine() {
    Medicine med;
    FILE *file = fopen(STOCK_FILE, "a");
    if (!file) {
        printf("Error: Could not open stock.txt\n");
        return;
    }

    med.id = get_next_id();

    printf("Enter medicine name: ");
    fgets(med.name, sizeof(med.name), stdin);
    med.name[strcspn(med.name, "\n")] = '\0';

    printf("Manufacture date (YYYY-MM-DD): ");
    fgets(med.mfg_date, sizeof(med.mfg_date), stdin);
    med.mfg_date[strcspn(med.mfg_date, "\n")] = '\0';

    printf("Expiry date (YYYY-MM-DD): ");
    fgets(med.exp_date, sizeof(med.exp_date), stdin);
    med.exp_date[strcspn(med.exp_date, "\n")] = '\0';

    printf("Price: ");
    scanf("%f", &med.price);
    printf("Quantity: ");
    scanf("%d", &med.quantity);
    getchar(); // clear newline

    fprintf(file, "%d,%s,%s,%s,%.2f,%d\n",
            med.id, med.name, med.mfg_date, med.exp_date, med.price, med.quantity);
    fclose(file);

    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "added %d %s to stock.", med.quantity, med.name);
    write_log(get_logged_in_user(), log_msg);

    printf("Medicine added successfully.\n");
}

void view_medicines() {
    FILE *file = fopen(STOCK_FILE, "r");
    if (!file) {
        printf("No stock available.\n");
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

void update_medicine() {
    int id, found = 0;
    printf("Enter medicine ID to update quantity: ");
    scanf("%d", &id);
    getchar();

    FILE *file = fopen(STOCK_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file.\n");
        return;
    }

    Medicine med;
    while (fscanf(file, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &med.id, med.name, med.mfg_date, med.exp_date, &med.price, &med.quantity) == 6) {
        if (med.id == id) {
            found = 1;
            int new_qty;
            printf("Enter new quantity for %s: ", med.name);
            scanf("%d", &new_qty);
            getchar();
            med.quantity = new_qty;

            char log_msg[256];
            snprintf(log_msg, sizeof(log_msg), "updated quantity of %s to %d.", med.name, new_qty);
            write_log(get_logged_in_user(), log_msg);
        }
        fprintf(temp, "%d,%s,%s,%s,%.2f,%d\n",
                med.id, med.name, med.mfg_date, med.exp_date, med.price, med.quantity);
    }
    fclose(file);
    fclose(temp);
    remove(STOCK_FILE);
    rename("temp.txt", STOCK_FILE);

    if (found)
        printf("Medicine updated.\n");
    else
        printf("Medicine not found.\n");
}

void delete_medicine() {
    int id, found = 0;
    printf("Enter medicine ID to delete: ");
    scanf("%d", &id);
    getchar();

    FILE *file = fopen(STOCK_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file.\n");
        return;
    }

    Medicine med;
    while (fscanf(file, "%d,%49[^,],%11[^,],%11[^,],%f,%d\n",
           &med.id, med.name, med.mfg_date, med.exp_date, &med.price, &med.quantity) == 6) {
        if (med.id == id) {
            found = 1;
            char log_msg[256];
            snprintf(log_msg, sizeof(log_msg), "deleted medicine %s.", med.name);
            write_log(get_logged_in_user(), log_msg);
            continue; // skip writing this line
        }
        fprintf(temp, "%d,%s,%s,%s,%.2f,%d\n",
                med.id, med.name, med.mfg_date, med.exp_date, med.price, med.quantity);
    }
    fclose(file);
    fclose(temp);
    remove(STOCK_FILE);
    rename("temp.txt", STOCK_FILE);

    if (found)
        printf("Medicine deleted.\n");
    else
        printf("Medicine ID not found.\n");
}
