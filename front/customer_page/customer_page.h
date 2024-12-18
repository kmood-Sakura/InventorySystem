#ifndef CUSTOMER_PAGE_H
#define CUSTOMER_PAGE_H

#include "search_goods_page.h"
#include "order_page.h"
#include "../../handler/access_owner_page.h"
#include "../owner_page/owner_page.h"
#include "../../back/database/struct/user.h"
#include "../../back/database/struct/auth.h"

void Customer_Page(AUTH* auth);

#endif