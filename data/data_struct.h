#ifndef GOODS_H
#define GOODS_H

#define MAX_ID_LEN 10
#define MAX_NAME_LEN 50
#define MAX_DESC_LEN 200

typedef struct {
    char id[MAX_ID_LEN]; // Unique ID for the goods
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    double price; // Price of the goods
    int stock; // Quantity in stock
} Goods;

#endif