#include <stdio.h>
#include <stdlib.h>
#include "../handler/login_handler.h"
#include "customer_page/customer_page.h"
#include "owner_page/owner_page.h"

int main(){
    AUTH *auth = (AUTH *)malloc(sizeof(AUTH));
    if (auth == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // Exit with error code
    }
    auth->customer = 0; auth->owner = 0;
    Customer_Page(auth);
    free(auth);
    return 0;
}