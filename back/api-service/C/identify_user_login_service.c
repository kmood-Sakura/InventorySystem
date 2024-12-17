#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../identify_user_login_service.h"


int identify_user_login(const char* email, const char *password){
    int userCount;
    USER* users = getUSERCSV("back/database/","user",&userCount);
    for(int i=0; i<userCount ;i++){
        printf("mail : %s\n",users[i].email);
        if (strcmp(users[i].email, email) == 0){
            if(strcmp(users[i].password, password) == 0){
                printf("\n");
                printf("--------------------------------------------------------\n");
                printf("\n");
                printf("Welcome, %s!\n", users[i].name);
                printf("\n");
                return 1;
            }else{
                printf("\n");
                printf("Invalid password. Try again.\n");
                printf("\n");
                printf("--------------------------------------------------------\n");
                return 0;
            }
        }
    }
    //martin

    return 0;
}

int userExist(USER* user){
    int userCount;
    USER* users = getUSERCSV("back/database/","user",&userCount);
    for(int i=0; i<userCount ;i++){
        if (
            strcmp(users[i].email, user->email) == 0 ||
            strcmp(users[i].name, user->name) == 0 ||
            strcmp(users[i].phone, user->phone) == 0
        ){
            return 0;
        }
    }
    //martin

    return 1;
}
