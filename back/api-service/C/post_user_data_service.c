#include <stdio.h>
#include "../post_user_data_service.h"

int POST_userdata(USER* userdata){
    //Piti Made it
    char *filename = "user";
    char *filepath = create_current_path("back/database/",filename,"csv");

    if(userExist(userdata,filepath)){
        perror("Error User already exist\n");
        return 0;
    }
    FILE* file = fopen(filepath,'a');
    if (file == NULL) {
        perror("Error opening file\n");
        return 0;
    }
    return 1;
}

int userExist(USER* user,char* data_path){
    USER* allUsers;
    int userCount;
    int exist = 0;

    // Assuming getUSERCSVpath returns a pointer to an array of USERs and the count
    allUsers = getUSERCSVpath(data_path, &userCount);

    if (allUsers == NULL) {
        return 0;  // Error reading users or file doesn't exist
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(user->name, allUsers[i].name) == 0) {
            printf("Username already exists\n");
            exist = 1;
        }
        if (strcmp(user->email, allUsers[i].email) == 0) {
            printf("Email already exists\n");
            exist = 1;
        }
        if (strcmp(user->phone, allUsers[i].phone) == 0) {
            printf("Phone number already exists\n");
            exist = 1;
        }
        if (exist) {
            free(allUsers);  // Don't forget to free the allocated memory
            return 0;
        }
    }

    free(allUsers);  // Free the allocated memory
    return 1;
}
//Martin
int verifyUserData(USER* userdata){
    if(!userdata->id){
        printf("id not found\n");
        return 0;
    }
    if(!userdata->name){
        printf("name not found\n");
        return 0;
    }
    if(!userdata->email){
        printf("email not found\n");
        return 0;
    }
    if(!userdata->phone){
        printf("phone number not found\n");
        return 0;
    }
    if(!userdata->password){
        printf("password not found");
        return 0;
    }
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