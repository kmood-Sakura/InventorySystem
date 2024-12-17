#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../login_handler.h"

#define USER_FILE "back/database/user.csv"

int loadUsers(USER users[], int *userCount);
int saveUser(USER *user);
int checkDuplicateUser(const USER *user, const USER users[], int userCount);
int Access_Owner_Page();

int isValidPhoneNumber(const char* phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

int tempBegin_Access(void) {
    return 1;
}

int Begin_Access(void) {
    char key;
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
    printf("Do you have an account?\ny : Yes\nn : No\ne : Exit\n");
    printf("\n");
    printf("Your choice: ");
    scanf(" %c", &key);
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
        
    key = toupper(key);

    switch (key) {
        case 'Y': return SignIn();
        case 'N': return SignUp();
        case 'E': exit(200);
        default: 
            printf("\n");
            printf("Invalid request (if you want to exit use key: 'e'). Please try again.\n");
            return Begin_Access();
    }
}

int SignUp() {
    USER* newUser = (USER*)malloc(sizeof(USER));
    if (!newUser) {
        printf("Memory allocation failed. Please try again.\n");
        return Begin_Access();
    }

    USER users[MAX_USER_DATA_LEN];
    int userCount = 0;

    if (!loadUsers(users, &userCount)) {
        printf("Error loading user data. Please try again later.\n");
        free(newUser);
        return Begin_Access();
    }

    while (getchar() != '\n'); 

    while (1) {
        printf("Enter your Name: ");
        fgets(newUser->name, MAX_USER_NAME_LEN, stdin);
        newUser->name[strcspn(newUser->name, "\n")] = 0;
        if (strlen(newUser->name) > 0) break;
        printf("Name cannot be empty. Please try again.\n");
    }

    while (1) {
        printf("Enter your Email: ");
        fgets(newUser->email, MAX_EMAIL_LEN, stdin);
        newUser->email[strcspn(newUser->email, "\n")] = 0;
        if (strlen(newUser->email) > 0) break;
        printf("Email cannot be empty. Please try again.\n");
    }

    while (1) {
        printf("Enter your Phone Number: ");
        fgets(newUser->phone, MAX_PHONE_NUM_LEN, stdin);
        newUser->phone[strcspn(newUser->phone, "\n")] = 0;

        if (isValidPhoneNumber(newUser->phone)) break;
        printf("Invalid phone number. Please enter exactly 10 digits.\n");
    }

    while (getchar() != '\n');

    while (1) {
        printf("Enter your Password: ");
        fgets(newUser->password, MAX_PASSWORD_LEN, stdin);
        newUser->password[strcspn(newUser->password, "\n")] = 0;
        if (strlen(newUser->password) > 0) break;
        printf("Password cannot be empty. Please try again.\n");
    }

    if (checkDuplicateUser(newUser, users, userCount)) {
        printf("\n");
        printf("A user with this email already exists. Please login instead.\n");
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("\n");
        free(newUser);
        return SignIn();
    }

    if (saveUser(newUser)) {
        printf("\n");
        printf("Account created successfully! You can now sign in.\n");
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("\n");
        free(newUser);
        return SignIn();
    }
    
    printf("\n");
    printf("Error saving the account. Please try again later.\n");
    free(newUser);
    return Begin_Access();
}

int SignIn() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    USER users[MAX_USER_DATA_LEN];
    int userCount = 0;

    if (!loadUsers(users, &userCount)) {
        printf("No accounts exist. Please sign up first.\n");
        return Begin_Access();
    }

    printf("Enter your Email: ");
    scanf("%s", email);

    printf("Enter your Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            printf("\n");
            printf("--------------------------------------------------------\n");
            printf("\n");
            printf("Welcome, %s!\n", users[i].name);
            printf("\n");
            return 1;
        }
    }

    printf("\n");
    printf("Invalid email or password. Try again.\n");
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\n");
    return SignIn();

}

// Load users from the file
int loadUsers(USER users[], int *userCount) {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        printf("Error: Unable to open user file: %s\n", USER_FILE);
        return 0;
    }

    char buffer[256];
    *userCount = 0;

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        int parsed = sscanf(buffer, FORMAT_USERDATA, 
                            users[*userCount].id, 
                            users[*userCount].name, 
                            users[*userCount].email, 
                            users[*userCount].phone, 
                            users[*userCount].password);
        if (parsed == 5) {
            (*userCount)++;
        } else {
            printf("Warning: Malformed line skipped: %s\n", buffer);
        }

        if (*userCount >= MAX_USER_DATA_LEN) {
            printf("Warning: Maximum user capacity reached. Some users may not be loaded.\n");
            break;
        }
    }

    fclose(file);
    return *userCount > 0;
}

// Save a new user to the file
int saveUser(USER *user) {
    FILE *file = fopen(USER_FILE, "a");
    if (!file) {
        return 0;
    }

    srand(time(NULL));
    int isUnique;
    char tempID[MAX_ID_LEN];
    do {
        sprintf(user->id, "%06d", rand() % 1000000);

        isUnique = 1;

        FILE *readFile = fopen(USER_FILE, "r");
        if (readFile) {
            char buffer[MAX_USER_DATA_LEN];
            fgets(buffer, sizeof(buffer), readFile);

            while (fgets(buffer, sizeof(buffer), readFile)) {
                sscanf(buffer, "%[^,]", tempID);
                if (strcmp(tempID, user->id) == 0) {
                    isUnique = 0;
                    break;
                }
            }
            fclose(readFile);
        }
    } while (!isUnique);

    fprintf(file, "%s,%s,%s,%s,%s\n", 
            user->id, user->name, user->email, user->phone, user->password);
    fclose(file);
    return 1;
}

// Check for duplicate user
int checkDuplicateUser(const USER *user, const USER users[], int userCount) {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        printf("Error: Could not open user file: %s\n", USER_FILE);
        return 1;
    }

    char buffer[MAX_USER_DATA_LEN];
    char tempID[MAX_ID_LEN], tempName[MAX_USER_NAME_LEN], tempEmail[MAX_EMAIL_LEN], tempPhone[MAX_PHONE_NUM_LEN], tempPassword[MAX_PASSWORD_LEN];

    if (!fgets(buffer, sizeof(buffer), file)) {
        printf("Error: Empty file or incorrect format.\n");
        fclose(file);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        int parsed = sscanf(buffer, FORMAT_USERDATA, tempID, tempName, tempEmail, tempPhone, tempPassword);

        if (parsed < 5) {
            if (strstr(buffer, user->email) != NULL) {
                fclose(file);
                return 1;
            }
            printf("Error: Malformed line: %s\n", buffer);
            continue;
        }

        if (strcmp(tempEmail, user->email) == 0) {
            printf("Duplicate found for email: %s\n", user->email);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
