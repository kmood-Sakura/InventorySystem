#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../access_owner_page.h"

#define OWNER_FILE "back/database/owner.csv"

int loadOwners(OWNER **owners, int *ownerCount) {
    *owners = getOWNERCSVpath(OWNER_FILE, ownerCount);
    return *ownerCount > 0;
}

int Access_Owner_Page(AUTH *auth) {
    OWNER *info = NULL;
    int ownerCount = 0;
    
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
    printf("Welcome to the Owner's Page! Token verification required.\n");
    printf("\n");
    if (!loadOwners(&info, &ownerCount)) {
        printf("Error: Unable to load owner data. Please contact the administrator.\n");
        return 0;
    }

    char enteredToken[MAX_TOKEN_LEN];
    int valid = 0;
    do{
        printf("Enter your Token: ");
        scanf(" %s",enteredToken);
        if (strlen(enteredToken) == 0) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        enteredToken[strcspn(enteredToken, "\n")] = 0;  
        printf("\n");
        
        if (strlen(enteredToken) == 0) {
            printf("Token cannot be empty. Please try again.\n");
            continue;
        }

        for(int i = 0; i < ownerCount; i++) {
            if (strcmp(enteredToken, info[i].token) == 0) {
                printf("--------------------------------------------------------\n");
                printf("\n");
                printf("Access granted! Welcome, Owner.\n");
                valid = 1;
                strcpy(auth->warehouseid,"main");
                auth->owner = 1;
                free(info);  // Free allocated memory
                return 1;
            } 
        }
        if(valid == 0) {
            printf("Invalid token. Please try again.\n");
        }
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("\n");
    }while(valid == 0);

    free(info);  // Free allocated memory if loop is somehow exited
    return 0;
}