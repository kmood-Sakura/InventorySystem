#ifndef WRITE_FILE_SERVICE_H
#define WRITE_FILE_SERVICE_H

#include "../../data/goods_struct.h"

#include "../../../handler/common_header/commonio.h"
//#include "../../handler/common_header/commonlib.h"
#include "../../../handler/common_header/commonstring.h"

void writeCSVrows(const char *filename, const Goods *data, int count);

#endif