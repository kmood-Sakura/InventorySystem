#ifndef SEARCH_GOODS_PAGE_H
#define SEARCH_GOODS_PAGE_H

#include "../../back/database/struct/inventory.h"
#include "../../back/common_service/get_goods_data_service.h"

void Search_Goods_Page(void);
int showALLGOODS(GOODS* items, int itemCount);
void Search_Common_Page(void);

#endif