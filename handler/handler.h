#ifndef HANDLER_H
#define HANDLER_H

#include "handler_struct.h"
#include "../data/data_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createCSVifNotExists(const char *filename, const char *headers);
int fileExists(const char *filename);
void createCSVfile(const char *filename, const char *headers);
void writeCSVrows(const char *filename, const Goods *data, int count);

Goods* readCSVfile(const char *filename, int *itemCount);

#endif