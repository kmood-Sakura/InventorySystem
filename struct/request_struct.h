#ifndef REQUEST_STRUCT_H
#define REQUEST_STRUCT_H

#define MAX_ID_LEN 11
#define MAX_NAME_LEN 51
#define MAX_DESC_LEN 201


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