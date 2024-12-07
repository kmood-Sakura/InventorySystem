#ifndef INVENTORY_H
#define INVENTORY_H

#include "../define/id.h"
#include "../define/goods_name.h"
#include "../define/description.h"

#define HEADER "id,name,description,price,quantity"
#define MAX_GOODS_DATA_LEN (MAX_ID_LEN + MAX_GOODS_NAME_LEN + MAX_DESC_LEN + 17 + 8 + 5)

typedef struct{
    char id[MAX_ID_LEN];
    char name[MAX_GOODS_NAME_LEN];
    char description[MAX_DESC_LEN];
    double price;
    int quantity; // >= 0
}GOODS;

#endif