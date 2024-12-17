#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../owner_page.h"

// void Owner_Page(void){
//     while(1){
//         char key;
//         printf("system command : ");
//         scanf(" %c",&key);
//         switch (key){
//             case 'O': Apply_Order_Page();
//                 break;
//             case 'S': Search_Warehouse_Inventory();
//                 break;
//             case '+': Add_Page();
//                 break;
//             case '-': Minus_Page();
//                 break;
//             case 'E': exit(200);
//             case 'A': //Access_Owner_Page();
//                 break;
//             default:
//                 printf("Invalid Key Command. Please Enter Again\n");
//                 break;
//         }
//     }
// }

//new

void Owner_Page(AUTH *auth) {
    //printf("owner id : %s\n",auth->ownerid);
    if (!auth->owner) { // Check if owner ID is not set
        if (!Access_Owner_Page(auth)) { // Attempt to authorize
            printf("Authorization failed. Returning to Customer Page.\n");
            Customer_Page(auth);
            return; // Exit if authorization fails
        }
    }
    printf("Welcome to the Owner Management System.\n");
    printf("Here are the available commands:\n");
    printf("  O: Apply an order. Navigate to the Order Page.\n");
    printf("  S: Search the warehouse inventory.\n");
    printf("  +: Add new items to the inventory.\n");
    printf("  -: Remove items from the inventory.\n");
    printf("  E: Exit the system.\n");
    printf("  B: Go back to customer page.\n");
    printf("Enter your command below:\n");

    while (1) {
        char key;
        printf("\nSystem command: ");
        scanf(" %c", &key);

        switch (key) {
            case 'O':
                printf("Navigating to the Order Page...\n");
                Apply_Order_Page();
                break;

            case 'S':
                printf("Searching the warehouse inventory...\n");
                Search_Warehouse_Inventory();
                break;

            case '+':
                printf("Adding new items to the inventory...\n");
                Add_Page();
                break;

            case '-':
                printf("Removing items from the inventory...\n");
                Minus_Page();
                break;

            case 'E':
                printf("Exiting the system. Goodbye!\n");
                exit(200);

            case 'B':
                printf("Advanced owner settings are not yet implemented.\n");
                Customer_Page(auth);
                break;

            default:
                printf("Invalid Key Command. Please try again.\n");
                break;
        }
    }
}
