#ifndef GET_GOODS_DATA_SERVICE_H
#define GET_GOODS_DATA_SERVICE_H

#include "../database/struct/inventory.h"
#include "path_service.h"

int parseGOODSCSVLine(char *line, GOODS *item);
GOODS* getGOODSCSV(const char* directory, const char *filename, int *itemCount);
GOODS* getGOODSCSVpath(const char *filepath, int *itemCount);
void printGOODS(const GOODS *item);
int showALLGOODS(GOODS* items, int itemCount);

int printByPriceDescending(GOODS* goods, int itemCount);
int printByPriceAscending(GOODS* goods, int itemCount);
int printByQuantityDescending(GOODS* goods, int itemCount);
int printByQuantityAscending(GOODS* goods, int itemCount);

#endif