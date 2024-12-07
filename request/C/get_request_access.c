#include <stdio.h>

#include "../get_request_access.h"

// example to do 1
int tempLogin1(loginRequest* req){
    printf("email : ");
    scanf("%s", req->email);
    printf("password : ");
    scanf("%s", req->password);

    if(req->email[0] == '\0' || req->password == '\0'){
        printf("invalid get login request\n");
        return 0;
    }   
    return 1;
}

// example to do 2
loginRequest* tempLogin2(){
    loginRequest* user_info = malloc(sizeof(loginRequest));
    if (user_info == NULL) {
        // Handle allocation error
        return NULL;
    }
    printf("email: ");
    scanf("%s", user_info->email);
    printf("password: ");
    scanf("%s", user_info->password);
    return user_info; // Return pointer to allocated memory
}

//worse example
loginRequest* WorseLogin(){
    loginRequest user_info; //after doen this function all variable will disappeared
    printf("email : ");
    scanf("%s", user_info.email);
    printf("password : ");
    scanf("%s", user_info.password);
    return &user_info;
}

//----------------------------------ur turn--MARTIN--------!!!
int getRequestLogin(){

    //martin

    return 0;
}

int getRequestSignIn(){

    //martin

    return 0;
}