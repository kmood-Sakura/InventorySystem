#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../search_goods_page.h"

void Search_Goods_Page(void) {
    printf("Search for goods\n");

    // Get the goods name to search for
    char goodsName[MAX_GOODS_NAME_LEN];  // Ensure we handle the correct size
    printf("Enter goods name to search: ");
    scanf("%s", goodsName);

    // Search all items that have the same name
    int itemCount;
    GOODS* items = getGOODSCSV("back/user/1/", "inventory", &itemCount);

    if (items == NULL || itemCount == 0) {
        printf("No products found.\n");
        return;
    }

    // Display all the results
    printf("Searching for products matching: %s\n", goodsName);
    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        // Check if the product name matches (partial match)
        if (strcmp(items[i].name, goodsName) == 0) {
            showALLGOODS(&items[i], 1);  // Show matching product
            found = 1;
        }
    }

    if (!found) {
        printf("No products found matching the name %s.\n", goodsName);
    }

    free(items);  // Free memory after use
}

// Function to display all products
void Search_Common_Page(void) {
    int itemCount;
    GOODS* items = getGOODSCSV("back/user/1/", "inventory", &itemCount);
    showALLGOODS(items, itemCount);
    free(items);
}