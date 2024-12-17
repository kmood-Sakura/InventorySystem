#ifndef GET_OWNER_DATA_SERVICE_H
#define GET_OWNER_DATA_SERVICE_H

#include "../database/struct/owner.h"
#include "path_service.h"
OWNER* getOWNERCSV(const char* directory, const char *filename, int *itemCount);
OWNER* getOWNERCSVpath(const char *filepath, int *itemCount);
void printOWNER(const OWNER *item);
int showALLOWNER(OWNER* items, int itemCount);

#endif