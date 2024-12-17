#ifndef IDENTIFY_USER_LOGIN_H
#define IDENTIFY_USER_LOGIN_H

#include "../../request/get_request_access.h"
#include "../common_service/get_user_data_service.h"

int identify_user_login(const char* email, const char *password);

#endif