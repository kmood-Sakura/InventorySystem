#ifndef GET_GOODS_DATA_SERVICE_H
#define GET_GOODS_DATA_SERVICE_H

#include "../database/struct/inventory.h"
#include "path_service.h"

int parseGOODSCSVLine(char *line, GOODS *item);
GOODS* getGOODSCSV(const char* directory, const char *filename, int *itemCount);
GOODS* getGOODSCSVpath(const char *filepath, int *itemCount);
void printGOODS(const GOODS *item);

#endif