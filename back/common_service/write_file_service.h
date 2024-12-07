#ifndef WRITE_FILE_SERVICE_H
#define WRITE_FILE_SERVICE_H

#include "../database/struct/inventory.h"
#include "path_service.h"

void writeCSVrows(const char* data_directory, const char *filename, const GOODS *data, int count);

#endif