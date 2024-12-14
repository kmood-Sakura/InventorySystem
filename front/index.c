#include <stdio.h>

#include "../handler/login_handler.h"
#include "book_page/book_page.h"
int main(){
    if(tempBegin_Access()){
        Book_Page();
    }
    return 0;
}