#ifndef REQUEST_STRUCT_H
#define REQUEST_STRUCT_H

#include "../data/goods_struct.h"

typedef struct{
    char name[MAX_NAME_LEN];
    double price;
    char condition_price;  // >, <, =
}userFilter;

typedef struct{
    char id[11];
}reachGoods;

//Book need to use
typedef struct{

}originFilter;
#endif