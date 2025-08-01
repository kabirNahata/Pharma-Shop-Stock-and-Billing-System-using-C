// login.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

#define MAX_USERS 10

static char current_user[20]; // store logged in username

const char* get_logged_in_user() {
    return current_user;
}

// Trim newline character
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') str[len-1] = '\0';
}

int login() {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error: Could not open users.txt\n");
        return 0;
    }

    User users[MAX_USERS];
    int user_count = 0;

    while (fscanf(file, "%19[^,],%19[^\n]\n", 
            users[user_count].username, 
            users[user_count].password) == 2) {
        user_count++;
        if (user_count >= MAX_USERS) break;
    }
    fclose(file);

    char username[20], password[20];
    int attempts = 0;
    while (attempts < 3) {
        printf("\n=== Login ===\n");
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        trim_newline(username);

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        trim_newline(password);

        for (int i = 0; i < user_count; i++) {
            if (strcmp(username, users[i].username) == 0 &&
                strcmp(password, users[i].password) == 0) {
                strcpy(current_user, username);
                printf("Login successful. Welcome, %s!\n", username);
                return 1;
            }
        }

        printf("Invalid credentials. Try again.\n");
        attempts++;
    }

    return 0;
}
