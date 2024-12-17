#include <stdio.h>
#include "../post_user_data_service.h"

int POST_userdata(USER* userdata){
    //Piti Made it
    char *filename = "user";
    char *filepath = "back/database/user.csv";

    if(userExist(userdata)){
        perror("Error User already exist\n");
        return 0;
    }
    FILE* file = fopen(filepath,'a');
    if (file == NULL) {
        perror("Error opening file\n");
        return 0;
    }
    
    if(writeuserData(userdata,file)){
        return 1;
    }
    printf("Insert Data Error\n");
    return 0;
}

int userExist(USER* user){
    int userCount;
    USER* users = getUSERCSV("back/database/","user.csv",&userCount);
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


int writeuserData(USER* userdata,FILE* file){
    fprintf(file,FORMAT_USERDATA,
            userdata->id,
            userdata->name,
            userdata->email,
            userdata->phone,
            userdata->password
    );
    return 1;
}