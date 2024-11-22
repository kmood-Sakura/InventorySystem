#ifndef READ_FILE_SERVICE_H
#define READ_FILE_SERVICE_H

#include "../../../handler/common_header/commonio.h"
#include "../../../handler/common_header/commonlib.h"
#include "../../../handler/common_header/commonstring.h"
#include "../../../data/goods_struct.h"

int countCSVLines(const char *filename);
int parseCSVLine(char *line, Goods *item);
void printGoods(const Goods *item);

#endif