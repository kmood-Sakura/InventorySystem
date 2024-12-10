#ifndef GET_USER_DATA_SERVICE_H
#define GET_USER_DATA_SERVICE_H

#include "../database/struct/user.h"
#include "path_service.h"

int parseUSERCSVLine(char *line, USER *users);
USER* getUSERCSV(const char *filename, int* usersCount);
USER* getUSERCSVpath(const char* filepath, int *usersCount);
void printUSER(const USER *users);

#endif