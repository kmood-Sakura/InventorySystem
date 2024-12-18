#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../search_goods_page.h"

void Search_Goods_Page(AUTH *auth) {
    printf("Search for goods\n");

    // Ask the user if they want to search by ID, name, or view all products
    printf("Choose an option:\n");
    printf("(1) Search by ID\n");
    printf("(2) Search by Name\n");
    printf("(3) View All Products\n");
    printf("Enter 1, 2, or 3: ");
    int searchType;
    scanf("%d", &searchType);

    // Load all items from the inventory
    int itemCount;
    GOODS* items = getGOODSCSV("back/user/1/", "inventory", &itemCount);

    if (items == NULL || itemCount == 0) {
        printf("No products found.\n");
        return;
    }

    // Handle different search/view options
    switch(searchType) {
        case 1: // Search by ID
            {
                char searchTerm[MAX_GOODS_NAME_LEN];
                printf("Enter goods ID to search: ");
                scanf("%s", searchTerm);

                int found = 0;
                printf("Searching for products matching ID: %s\n", searchTerm);
                for (int i = 0; i < itemCount; i++) {
                    if (strcmp(items[i].id, searchTerm) == 0) {
                        showALLGOODS(&items[i], 1);
                        found = 1;
                    }
                }

                if (!found) {
                    printf("No products found matching the ID: %s.\n", searchTerm);
                }
            }
            break;

        case 2: // Search by Name
            {
                char searchTerm[MAX_GOODS_NAME_LEN];
                printf("Enter goods name to search: ");
                scanf("%s", searchTerm);

                int found = 0;
                printf("Searching for products matching name: %s\n", searchTerm);
                for (int i = 0; i < itemCount; i++) {
                    if (strcmp(items[i].name, searchTerm) == 0) {
                        showALLGOODS(&items[i], 1);
                        found = 1;
                    }
                }

                if (!found) {
                    printf("No products found matching the name: %s.\n", searchTerm);
                }
            }
            break;

        case 3: // View All Products
            printf("Displaying All Products:\n");
            printf("ID\tName\tDescricption\tPrice\tQuantity\n");
            printf("---------------------------------------------------------\n");
            for (int i = 0; i < itemCount; i++) {
                printf("%06s\t%0s\t%s\t%.2f\t%d\n",
                       items[i].id, items[i].name, items[i].description,
                       items[i].price, items[i].quantity);
            }
            break;

        default:
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
    }

    free(items); // Free memory after use
}