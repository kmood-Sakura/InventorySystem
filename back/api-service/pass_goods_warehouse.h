#ifndef PASS_GOODS_WAREHOUSE_H
#define PASS_GOODS_WAREHOUSE_H

#include "../common_service/update_file_service.h"

int addGOODSToWarehouse(const char* warehouse_name,const char* main_warehouse_name,const char* filename, const char* goodsID, int quantity);

#endif