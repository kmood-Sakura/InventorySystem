#ifndef ACCESS_OWNER_PAGE_H
#define ACCESS_OWNER_PAGE_H

#include "../back/database/struct/owner.h"
#include "../back/database/struct/auth.h"
#include "../back/database/define/line_data.h"
#include "../back/common_service/get_owner_data_service.h"

int Access_Owner_Page(AUTH *auth);

#endif