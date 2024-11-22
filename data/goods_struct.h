#ifndef GOODS_STRUCT_H
#define GOODS_STRUCT_H

#include "partner_struct.h"

typedef struct {
    char description[MAX_DESC_LEN];
    Address origin;
    Partner supplier;
} Detail;

typedef struct {
    char id[MAX_ID_LEN];        // Unique ID for the goods
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    double price;                // Price of the goods
    int stock;                   // Quantity in stock
    
    //---------------------------------
    //Detail detail;            //temperary change to description
    //---------------------------------                 
} Goods;

#endif // GOODS_STRUCT_H