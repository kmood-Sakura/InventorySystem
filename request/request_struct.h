#ifndef REQUEST_STRUCT_H
#define REQUEST_STRUCT_H

typedef struct{
    char name[51];
    double price;
    char condition_price;
}userFilter;

typedef struct{
    char id[11];
}reachGoods;

#endif