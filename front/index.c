#include <stdio.h>

#include "../handler/login_handler.h"
#include "customer_page/customer_page.h"
//#include "owner_page/owner_page.h"

int main(){
    if(tempBegin_Access()){
        Customer_Page();
    }
    return 0;
}