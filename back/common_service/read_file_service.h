#ifndef READ_FILE_SERVICE_H
#define READ_FILE_SERVICE_H

#include "../database/define/line_data.h"

FILE* readFile(const char* filepath);
int countCSVLines(FILE* csvfile);

#endif