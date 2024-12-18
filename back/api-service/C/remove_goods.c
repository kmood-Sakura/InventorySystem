#include <stdio.h>

#include "../pass_goods_warehouse.h"

int removeGOODSFromWarehouse(const char* warehouse_id,const char* filename, const char* goodsID, int quantity) {
    char *maindir = create_warehouse_dir("back/warehouse/",warehouse_id);
    if(!update_item_quantity(maindir,filename,goodsID,-quantity)){
        printf("Error : not enough item in inventory\n");
        return 0;
    }

    return 1;
}