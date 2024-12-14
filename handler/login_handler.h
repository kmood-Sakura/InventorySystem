#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include "../back/database/struct/user.h"

int tempBegin_Access();
int Begin_Access();
int SignIn();
int SignUp();
int Access_Owner_Page();

#endif