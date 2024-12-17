#ifndef OWNER_H
#define OWNER_H

#include "../define/name.h"
#include "../define/id.h"

#define HEADER_OWNERDATA "id,token,name"
#define FORMAT_OWNERDATA "%[^,],%[^,],%[^,]\n"

#define MAX_WAREHOUSE_ID_LEN 3
#define MAX_TOKEN_LEN 64
#define MAX_OWNER_DATA_LEN (MAX_WAREHOUSE_ID_LEN + MAX_TOKEN_LEN + MAX_NAME_LEN + 5)

typedef struct {
    char warehouseid[MAX_WAREHOUSE_ID_LEN];
    char id[MAX_ID_LEN];
    char token[MAX_TOKEN_LEN];
    char name[MAX_NAME_LEN];
}OWNER;


#endif
