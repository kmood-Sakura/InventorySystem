#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../access_owner_page.h"

#define OWNER_FILE "back/database/owner.csv"

int loadOwners(OWNER owners[], int *ownerCount);

int Access_Owner_Page() {
    char enteredToken[MAX_TOKEN_LEN];
    OWNER info[MAX_LINE_DATA_LEN];
    int ownerCount = 0;
    
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
    printf("Welcome to the Owner's Page! Token verification required.\n");
    printf("\n");

    if (!loadOwners(info, &ownerCount)) {
        printf("Error: Unable to load owner data. Please contact the administrator.\n");
        return 0;
    }

    while (getchar() != '\n'); 

    while (1) {
        printf("Enter your Token: ");
        fgets(enteredToken, sizeof(enteredToken), stdin);
        enteredToken[strcspn(enteredToken, "\r\n")] = 0;  
        printf("\n");
        
        if (strlen(enteredToken) == 0) {
            printf("Token cannot be empty. Please try again.\n");
            continue;
        }

        //check -------------------
        int valid = 0;
        for(int i = 0; i < ownerCount; i++) {
            if (strcmp(enteredToken, info[i].token) == 0) {
                printf("--------------------------------------------------------\n");
                printf("\n");
                printf("Access granted! Welcome, Owner.\n");
                valid = 1;
                return 1;
            } 
        }
        if(valid == 0) {
            printf("Invalid token. Please try again.\n");
        }
        //-----------
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("\n");
    }

    return 1;
}

int loadOwners(OWNER owners[], int *ownerCount) {
    FILE *file = fopen(OWNER_FILE, "r");
    if (!file) {
        printf("Error: Unable to open owner file: %s\n", OWNER_FILE);
        return 0;
    }

    char buffer[256];
    *ownerCount = 0;

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        int parsed = sscanf(buffer, FORMAT_OWNERDATA, 
                            owners[*ownerCount].id, 
                            owners[*ownerCount].token, 
                            owners[*ownerCount].name);
        if (parsed == 3) {
            (*ownerCount)++;
        } else {
            printf("Warning: Malformed line skipped: %s\n", buffer);
        }

        if (*ownerCount >= MAX_OWNER_DATA_LEN) {
            printf("Warning: Maximum owner capacity reached. Some owners may not be loaded.\n");
            break;
        }
    }

    fclose(file);
    return *ownerCount > 0;
}