#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../get_user_data_service.h"

// Function to parse one CSV line into a USER struct
int parseUSERCSVLine(char *line, USER *users) {
    char *token;
    int field = 0;
    
    // Skip empty lines
    if (strlen(line) <= 1) return 0;
    
    // Remove newline character if present
    line[strcspn(line, "\n")] = 0;
    
    // Get first token (ID)
    token = strtok(line, ",");
    while (token != NULL && field < 5) {  // 5 fields in USER struct
        // Remove quotes if present
        if (token[0] == '"') {
            token++;
            token[strlen(token)-1] = '\0';
        }
        
        switch(field) {
            case 0:  // ID
                strncpy(users->id, token, MAX_ID_LEN - 1);
                users->id[MAX_ID_LEN - 1] = '\0';
                break;
            case 1:  // Name
                strncpy(users->name, token, MAX_USER_NAME_LEN - 1);
                users->name[MAX_USER_NAME_LEN - 1] = '\0';
                break;
            case 2:  // Email
                strncpy(users->email, token, MAX_EMAIL_LEN - 1);
                users->email[MAX_EMAIL_LEN - 1] = '\0';
                break;
            case 3:  // Phone
                strncpy(users->phone, token, MAX_PHONE_NUM_LEN - 1);
                users->phone[MAX_PHONE_NUM_LEN - 1] = '\0';
                break;
            case 4:  // quantity
                strncpy(users->password, token, MAX_PASSWORD_LEN - 1);
                users->password[MAX_PASSWORD_LEN - 1] = '\0';
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    
    return (field == 5) ? 1 : 0;  // Return 1 if all fields were read
}

USER* getUSERCSVpath(const char* filepath, int *usersCount){
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    USER *users = NULL;
    int capacity = 10;  // Initial capacity
    *usersCount = 0;

    users = (USER*)malloc(capacity * sizeof(USER));
    if (users == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_USER_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*usersCount >= capacity) {
            capacity *= 2;
            USER *temp = realloc(users, capacity * sizeof(USER));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(users);
                fclose(file);
                return NULL;
            }
            users = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d", 
               users[*usersCount].id, 
               users[*usersCount].name, 
               users[*usersCount].email, 
               users[*usersCount].phone, 
               users[*usersCount].password);
        
        (*usersCount)++;
    }

    fclose(file);
    return users;
}

USER* getUSERCSV(const char* directory, const char *filename, int *usersCount) {

    char *filepath = create_current_path(directory, filename, "csv");
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    USER *users = NULL;
    int capacity = 10;  // Initial capacity
    *usersCount = 0;

    users = (USER*)malloc(capacity * sizeof(USER));
    if (users == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_USER_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*usersCount >= capacity) {
            capacity *= 2;
            USER *temp = realloc(users, capacity * sizeof(USER));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(users);
                fclose(file);
                return NULL;
            }
            users = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d", 
               users[*usersCount].id, 
               users[*usersCount].name, 
               users[*usersCount].email, 
               users[*usersCount].phone, 
               users[*usersCount].password);
        
        (*usersCount)++;
    }

    fclose(file);
    return users;
}

// Function to print GOODS for verification
void printGOODS(const USER *user) {
    printf("ID: %s\n", user->id);
    printf("Name: %s\n", user->name);
    printf("Email: %s\n", user->email);
    printf("Phone: %.10s\n", user->phone);
    //printf("password: %s\n", user->password);
    printf("------------------------\n");
}