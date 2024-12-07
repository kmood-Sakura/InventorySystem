#ifndef GET_REQUEST_ACCESSS_H
#define GET_REQUEST_ACCESSS_H

#include "../back/database/struct/user.h"

typedef struct{
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
}loginRequest;

void getRequestLogin();
void getRequestSignIn();

#endif