#ifndef POST_USER_DATA_SERVICE_H
#define POST_USER_DATA_SERVICE_H

#include "../../database/struct/user.h"
#include "../common_service/path_service.h"
#include "../common_service/get_user_data_service.h"

int POST_userdata(USER* userdata);
int userExist(USER* user);

#endif