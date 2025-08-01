// structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char username[20];
    char password[20];
} User;

typedef struct {
    int id;
    char name[50];
    char mfg_date[12];
    char exp_date[12];
    float price;
    int quantity;
} Medicine;

typedef struct {
    char name[100];
    char address[200];
    char logo[1000]; // optional ASCII logo string
} PharmaInfo;

#endif
