#include <stdio.h>
#include <stdlib.h>
#include "../search_inventory_page.h"

void Search_Warehouse_Inventory(AUTH *auth) {
    char* filepath = create_full_path("back/warehouse/",auth->warehouseid, "/inventory", "csv");

    int itemCount; 
    GOODS* goods = getGOODSCSVpath(filepath, &itemCount);

    if (goods == NULL) {
        printf("Error loading goods data.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Show all goods\n");
        printf("2. Sort goods\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showALLGOODS(goods, itemCount);
                break;

            case 2: {
                int sortChoice;
                printf("\nChoose a sorting option:\n");
                printf("1. Sort by Price (High to Low)\n");
                printf("2. Sort by Price (Low to High)\n");
                printf("3. Sort by Quantity (High to Low)\n");
                printf("4. Sort by Quantity (Low to High)\n");
                printf("Enter your choice: ");
                scanf("%d", &sortChoice);

                switch (sortChoice) {
                    case 1:
                        printByPriceDescending(goods, itemCount);
                        break;

                    case 2:
                        printByPriceAscending(goods, itemCount);
                        break;

                    case 3:
                        printByQuantityDescending(goods, itemCount);
                        break;

                    case 4:
                        printByQuantityAscending(goods, itemCount);
                        break;

                    default:
                        printf("Invalid sort choice.\n");
                        break;
                }
                break;
            }

            case 3:
                printf("Exiting...\n");
                free(goods);  // Free the allocated memory
                return;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
