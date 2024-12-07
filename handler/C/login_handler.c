#include <stdio.h>
#include <stdlib.h>

#include "../login_handler.h"
#include "../../back/database/struct/user.h" //use struct infomation to continue developing function !!!!!

int tempBegin_Access(void){
    return 1;
}
int Begin_Access(void){
    char key;
    printf("want to create a account(y,n) : ");
    scanf(" %c",&key);
    switch (key){
        case 'y': return SignIn();
        case 'n': return Login();
        case 'e': exit(200);
        default:
            printf("invalid request (if you want to exit use key : 'e') please try again\n");
            return Begin_Access();
    }
}

int Login(){

    //martin
    
    return 1;
}

int SignIn(){

    //martin

    return 1;
}

int Access_Owner_Page(){

    //martin

    return 1;
}