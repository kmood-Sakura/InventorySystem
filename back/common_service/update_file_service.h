#ifndef UPDATE_H
#define UPDATE_H

#include "../database/struct/inventory.h"
#include "../database/define/line_data.h"
#include "../common_service/path_service.h"

int update_item_quantity(const char* directory, const char* filename, const char* item_id, int quantity_change);

#endif