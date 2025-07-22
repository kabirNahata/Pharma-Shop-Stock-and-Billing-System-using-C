#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10

typedef struct{
    char username[20];
    char password[20]''
} User ;

char current_user[20];

int load_user(User users[]){
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL){
        printf("Error: users.txt not found.\n");
        return 1;
    }

    int count = 0;
    while (fscanf(fp, "%s %s", users[count].username, users[count].password) != EOF){
        count++;
    }

    fclose(fp);
    return count;
}

int login(){
    User users[MAX_USERS];
    int user_count = load_user(users);

    char uname[20], pass[20];
    int attempt = 0;

    while (attempt < 3){
        printf("Enter username: ");
        scanf("%s", uname);
        printf("Enter password: ");
        scanf("%s", pass);

        for (int i = 0; i < user_count; i++){
            if (strcmp(uname, users[i].username) == 0 && strcmp(pass,users[i].password) == 0){
                printf("\nLogin successful! Welcome, %s\n\n", uname);
                strcpy(current_user, uname);
                return 1;
            }
        }
        attempt++;
        printf("Incoorect credentials. Try again. (%d/3) attempts left\n", attempt);
    }
    printf("\nToo many failed attempts. Exiting...\n");
    return 0;
}

int main(){
    printf("=== Pharma Shop Login ===\n");

    if (!login()){
        return 1;
    }

    return 0;
}













// #define MAX_USERNAME_LEN 20
// #define MAX_PASSWORD_LEN 20
// #define MAX_USERS 10

// typedef struct { 
// char username[MAX_USERNAME_LEN]; 
// char password[MAX_PASSWORD_LEN];
// } User;

// int load_users(User users[], int max_users);{
//     FILE *fp = fopen("users.txt", "r");
//     if (fp == NULL){
//         perror("Error opening users.txt.")
//         return 1;
//     }

//     int count = 0;
//     char line[MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 2];
//     while (fgets(line, sizeof(line), fp) != NULL && count < MAX_USERS){
//         line[strcspn(line, "\n")] = 0;


//     }
// }

// struct id {
//     User all_users[20];
// };

// int signup();
// int menu();

// int main(){
//     char pass[5];
//     printf("Do you have an account(yes/no)");
//     scanf("%s", &pass);

//     if (pass=="yes"){

//     }
//     else if (pass=="no")
//     {
//         int signup();
//     }
//     else{
//         printf("Invalid input, please enter (yes or no)")
//     }
//     return 0;
// }

// int menu(){

//     int choice;

//     printf("Please choose any option below(1 or 2)\n");
//     printf("1. Signup (dont have an account)\n");
//     printf("2. login (have an account)\n");
//     printf("OR\n");
//     printf("3. Exit\n");

//     if (scanf("%d", &choice) != 1) {
//         printf("Invalid input. Please enter a number.\n");
//     }

//     switch (choice){
//         case 1:
//             int signup();
//             break;
        
//         case 2:
//             int login();
//             break;
            
//         case 3:
//             searchStudent(students, size);
//             break;
//     }



// int signup(){
//     struct User new_user;
//     FILE *fp = fopen("users.txt", "w");
//     if (fp == NULL){
//         printf("Error: Could not open file 'users.txt'\n");
//         return 1;
//     }

//     printf("Enter your username: ");
//     scanf("%s", &new_user.username);

//     printf("Enter your password: ");
//     scanf("%s", &new_user.password);

//     fprintf(fp, "Username: %s, Password: %s\n", new_user.username, new_user.password);

//     fclose(fp);
//     printf("User data saved successfully!\n");
//     return 0;
// }

// int login(const char *username, const char *password)

