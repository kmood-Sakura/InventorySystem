#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "../back/database/struct/user.h"
#include "../back/database/struct/auth.h"
#include "../back/api-service/identify_user_login_service.h"
int tempBegin_Access();
int Begin_Access(AUTH *auth);
int SignIn(AUTH *auth);
int SignUp(AUTH *auth);
int Access_Owner_Page(AUTH *auth);

#endif