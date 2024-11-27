#ifndef PARTNER_STRUCT_H
#define PARTNER_STRUCT_H

#define MAX_ID_LEN 11
#define MAX_CALL_NUM_LEN 11
#define MAX_NAME_LEN 51
#define MAX_EMAIL_LEN 51
#define MAX_DESC_LEN 201

typedef struct {
    char country[MAX_NAME_LEN];
    char capital[MAX_NAME_LEN];
} Address;

typedef struct {
    char phone[MAX_CALL_NUM_LEN];
    char email[MAX_EMAIL_LEN];
    Address address;
} Contact;

typedef struct {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    Contact contact;
} Partner;

#endif // PARTNER_STRUCT_H