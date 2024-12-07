#ifndef ORDER_H
#define ORDER_H

#include "../define/id.h"

#define HEADER_ORDER "id,goodsid,userid,quantity"

typedef struct{
    char id[MAX_ID_LEN];
    char goodsID[MAX_ID_LEN];
    char userID[MAX_ID_LEN];
    int quantity;
}Order;


#endif