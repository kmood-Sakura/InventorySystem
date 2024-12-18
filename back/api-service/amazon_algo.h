#ifndef AMAZON_ALGO_H
#define AMAZON_ALGO_H

#include "../database/struct/warehouse.h"
#include "../common_service/get_goods_data_service.h"
#include "../database/struct/inventory.h"

typedef struct {
    WAREHOUSE warehouses[MAX_WAREHOUSES];
    int warehouse_count;
}DATA;

typedef struct {
    char id[MAX_ID_LEN];
    int maxQuantity;
} TempInfo;

int Amazon_Algo(const char* id);
int create_updated_stock(TempInfo *information, int infoCount, WAREHOUSE* warehouse);

#endif