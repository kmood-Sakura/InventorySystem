#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../search_goods_page.h"

void Search_Goods_Page(void) {
    printf("Search for goods\n");

    // Ask the user if they want to search by ID or name
    printf("Do you want to search by (1) ID or (2) Name? Enter 1 or 2: ");
    int searchType;
    scanf("%d", &searchType);

    // Get the search term
    char searchTerm[MAX_GOODS_NAME_LEN];
    if (searchType == 1) {
        printf("Enter goods ID to search: ");
    } else if (searchType == 2) {
        printf("Enter goods name to search: ");
    } else {
        printf("Invalid choice. Please enter 1 or 2.\n");
        return;
    }
    scanf("%s", searchTerm);

    // Load all items from the inventory
    int itemCount;
    GOODS* items = getGOODSCSV("back/user/1/", "inventory", &itemCount);

    if (items == NULL || itemCount == 0) {
        printf("No products found.\n");
        return;
    }

    // Display all the results
    int found = 0;
    printf("Searching for products matching: %s\n", searchTerm);
    for (int i = 0; i < itemCount; i++) {
        // Check if the product matches the search term
        if ((searchType == 1 && strcmp(items[i].id, searchTerm) == 0) ||
            (searchType == 2 && strcmp(items[i].name, searchTerm) == 0)) {
            showALLGOODS(&items[i], 1); // Show matching product
            found = 1;
        }
    }

    if (!found) {
        printf("No products found matching the %s: %s.\n", searchType == 1 ? "ID" : "name", searchTerm);
    }

    free(items); // Free memory after use
}

// Function to display all products
void Search_Common_Page(void) {
    int itemCount;
    GOODS* items = getGOODSCSV("back/user/1/", "inventory", &itemCount);
    showALLGOODS(items, itemCount);
    free(items);
}
