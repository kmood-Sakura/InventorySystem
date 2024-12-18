#ifndef ORDER_PAGE_H
#define ORDER_PAGE_H

#include "../../back/database/struct/inventory.h"
#include "../../back/common_service/update_file_service.h" 
#include "../../back/common_service/get_goods_data_service.h"
#include "../../back/api-service/coupon_service.h"
#include "../../back/common_service/log_service.h"
#include "../../back/database/struct/auth.h"

int get_quantity_input(int availableQuantity);
GOODS* find_product_by_name(GOODS* products, int itemCount, const char* goodsName);
void Order_Page(AUTH * auth);

#endif