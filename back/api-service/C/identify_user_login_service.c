#include <stdio.h>

#include "../identify_user_login_service.h"
#include "../../../request/get_request_access.h"
#include "../../common_service/get_user_data_service.h"

int identify_user_login(loginRequest *req){
    int userCount;
    USER* allUser = getUSERCSV("user.csv",&userCount);

    //martin

    return 0;
}