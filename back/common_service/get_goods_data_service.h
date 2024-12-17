#ifndef GET_GOODS_DATA_SERVICE_H
#define GET_GOODS_DATA_SERVICE_H

#include "../database/struct/inventory.h"
#include "path_service.h"

int parseGOODSCSVLine(char *line, GOODS *item);
GOODS* getGOODSCSV(const char *filename, int *itemCount);
GOODS* getGOODSCSVpath(const char *filepath, int *itemCount);

int showALLGOODS(GOODS* goods, int itemCount);
int printGOODS(const GOODS *item);

int printByPriceDescending(GOODS* goods, int itemCount);
int printByPriceAscending(GOODS* goods, int itemCount);
int printByQuantityDescending(GOODS* goods, int itemCount);
int printByQuantityAscending(GOODS* goods, int itemCount);

#endif