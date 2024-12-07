#ifndef USER_H
#define USER_H

#include "../define/user_name.h"
#include "../define/id.h"
#include "../define/email.h"
#include "../define/phone.h"
#include "../define/password.h"

#define HEADER_USERDATA "id,name,email,phone,password"
#define FORMAT_USERDATA "%s,%s,%s,%s,%s"
#define MAX_USER_DATA_LEN (MAX_ID_LEN + MAX_USER_NAME_LEN + MAX_EMAIL_LEN + MAX_PHONE_NUM_LEN + MAX_PASSWORD_LEN + 5)

typedef struct{
    char id[MAX_ID_LEN];
    char name[MAX_USER_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    char phone[MAX_PHONE_NUM_LEN];
    char password[MAX_PASSWORD_LEN];
}USER;

#endif