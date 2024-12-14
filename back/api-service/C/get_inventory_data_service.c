#include <stdio.h>
#include <stdlib.h>

#include "../get_inventory_data_service.h"

int getInventoryData(int *itemCount){
    char *filepath = create_current_path("back/warehouse/1","inventory","csv");
    GOODS* items = getGOODSCSVpath(filepath, *itemCount);
}