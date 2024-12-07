#include <stdio.h>

#include "../handler/login_handler.h"
//#include "customer_page/customer_page.h"
#include "owner_page/owner_page.h"

int main(){
    if(tempBegin_Access()){
        printf("auto go to owner page by pam\n");
        Owner_Page();
    }
    return 0;
}