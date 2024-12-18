#ifndef LOG_SERVICE_H
#define LOG_SERVICE_H

#include "../database/struct/inventory.h"
//#include "../database/struct/coupon.h"
#include "../database/struct/user.h"
#include "../database/struct/order.h"

void COMMON_log(const char* id,const char *type, const char * path_Data, int quanitty);
void GOODS_log(GOODS *goods, const char *type, const char * path_Data, int quanitty);
void USER_log(USER *user, const char *type, const char * path_Data, int quanitty);
//void Coupon_log(Coupon *coupon, const char *type, const char * path_Data, int quanitty);
void Order_log(Order *order, const char *type, const char * path_Data, int quanitty);

#endif