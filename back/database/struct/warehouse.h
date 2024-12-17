#ifndef WAREAHOUSE_H
#define WAREAHOUSE_H

#include "inventory.h"

#define MAX_WAREHOUSES 100

typedef struct {
    char id[MAX_ID_LEN];
    GOODS goods[MAX_GOODS];
    int goods_count;
} WAREHOUSE;

#endif