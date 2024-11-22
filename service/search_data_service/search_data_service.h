#ifndef SEARCH_DATA_SERVICE_H
#define SEARCH_DATA_SERVICE_H

#include "../../data/goods_struct.h"
#include "../../request/request_struct.h"
#include "../../handler/common_header/commonio.h"
#include "../../handler/common_header/commonlib.h"
#include "../../handler/common_header/commonstring.h"
#include "../common_service/read/read_file_service.h"

#define MAX_LINE_LENGTH 1024

int parseCSVLinebyFilter(char *line, Goods *item, userFilter *reqUserFilter);
Goods* searchCSVfile(const char *filename, int *itemCount, userFilter *reqUserFilter);
int FilterbyPrice(userFilter *reqUserFilter, Goods *item);

#endif