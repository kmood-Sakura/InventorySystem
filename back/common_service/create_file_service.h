#ifndef CREATE_FILE_H
#define CREATE_FILE_H

#include "path_service.h"

int createFile(const char* data_directory,const char *filename,const char* filetype);
int createFilePath(const char* filepath);
int createCSVfile(const char *filename, const char *headers);
int fileExists(const char* filepath);

#endif