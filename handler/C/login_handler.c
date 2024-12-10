#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../login_handler.h"

#define USER_FILE "back/database/user.csv"

// Function Prototypes
int loadUsers(USER users[], int *userCount);
int saveUser(USER *user); // Updated to modify user ID
int checkDuplicateUser(const USER *user, const USER users[], int userCount);
int Access_Owner_Page();

int tempBegin_Access(void) {
    return 1;
}

int Begin_Access(void) {
    char key;
    printf("Do you have an account? (y/n, e to exit): ");
    scanf(" %c", &key);

    switch (key) {
        case 'y': return SignIn();
        case 'n': return SignUp();
        case 'e': exit(200);
        default:
            printf("Invalid request (if you want to exit use key: 'e'). Please try again.\n");
            return Begin_Access();
    }
}

int SignIn() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    USER users[MAX_USER_DATA_LEN];
    int userCount = 0;

    // Load existing users
    if (loadUsers(users, &userCount) == 0) {
        printf("No accounts exist. Please sign up first.\n");
        return Begin_Access();
    }

    printf("Enter your Email: ");
    scanf("%s", email);
    printf("Enter your Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Welcome back, %s!\n", users[i].name);
            return Access_Owner_Page();
        }
    }

    printf("Invalid email or password. Try again.\n");
    return SignIn();
}

int SignUp() {
    // Allocate memory for the new user
    USER* newUser = (USER*)malloc(sizeof(USER));
    if (!newUser) {
        printf("Memory allocation failed. Please try again.\n");
        return Begin_Access();
    }

    USER users[MAX_USER_DATA_LEN];
    int userCount = 0;

    // Load existing users
    if (!loadUsers(users, &userCount)) {
        printf("Error loading user data. Please try again later.\n");
        free(newUser);
        return Begin_Access();
    }

    // Get Name (Full name including spaces)
    printf("Enter your Name: ");
    fgets(newUser->name, MAX_USER_NAME_LEN, stdin);
    newUser->name[strcspn(newUser->name, "\n")] = 0; // Remove trailing newline

    // Validate Name
    if (strlen(newUser->name) == 0) {
        printf("Name cannot be empty. Please try again.\n");
        free(newUser);
        return SignUp();
    }

    // Get Email
    printf("Enter your Email: ");
    scanf("%s", newUser->email);

    // Validate Email
    if (strlen(newUser->email) == 0) {
        printf("Email cannot be empty. Please try again.\n");
        free(newUser);
        while (getchar() != '\n'); // Clear buffer
        return SignUp();
    }

    // Clear buffer after scanf
    while (getchar() != '\n');

    // Get Phone Number
    printf("Enter your Phone Number: ");
    fgets(newUser->phone, MAX_PHONE_NUM_LEN, stdin);
    newUser->phone[strcspn(newUser->phone, "\n")] = 0;

    // Validate Phone Number
    if (strlen(newUser->phone) == 0) {
        printf("Phone number cannot be empty. Please try again.\n");
        free(newUser);
        return SignUp();
    }

    // Get Password
    printf("Enter your Password: ");
    fgets(newUser->password, MAX_PASSWORD_LEN, stdin);
    newUser->password[strcspn(newUser->password, "\n")] = 0;

    // Validate Password
    if (strlen(newUser->password) == 0) {
        printf("Password cannot be empty. Please try again.\n");
        free(newUser);
        return SignUp();
    }

    // Check for duplicate users
    if (checkDuplicateUser(newUser, users, userCount)) {
        printf("User with the same email or ID already exists. Please try again.\n");
        free(newUser);
        return SignUp();
    }

    // Save the new user
    if (saveUser(newUser)) {
        printf("Account created successfully! You can now sign in.\n");
        free(newUser);
        return SignIn();
    }

    // Handle save error
    printf("Error saving the account. Please try again later.\n");
    free(newUser);
    return Begin_Access();
}



int Access_Owner_Page() {
    printf("Welcome to the Owner's Page! You have full access.\n");
    // Placeholder for owner-specific functionality
    return 1;
}

// Load users from the file
int loadUsers(USER users[], int *userCount) {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        return 0;
    }

    char buffer[MAX_USER_DATA_LEN];
    *userCount = 0;

    // Skip header
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, FORMAT_USERDATA,
               users[*userCount].id,
               users[*userCount].name,
               users[*userCount].email,
               users[*userCount].phone,
               users[*userCount].password);
        (*userCount)++;
    }

    fclose(file);
    return 1;
}

// Save a new user to the file
int saveUser(USER *user) {
    FILE *file = fopen(USER_FILE, "a");
    if (!file) {
        return 0;
    }

    // Generate a unique 6-digit random ID
    srand(time(NULL));
    int isUnique;
    char tempID[MAX_ID_LEN];
    do {
        // Generate a 6-digit random number, ensuring it's exactly 6 digits long
        sprintf(user->id, "%06d", rand() % 1000000);

        isUnique = 1;

        // Open the file to check if the generated ID is unique
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

    // Write the user's data to the file
    fprintf(file, FORMAT_USERDATA, 
            user->id, user->name, user->email, user->phone, user->password);
    fclose(file);
    return 1;
}

// Check for duplicate user (ID or email)
int checkDuplicateUser(const USER *user, const USER users[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, user->id) == 0 || strcmp(users[i].email, user->email) == 0) {
            return 1;
        }
    }
    return 0;
}
