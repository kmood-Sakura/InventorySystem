#include <stdio.h>

#include "../minus_page.h"

void Minus_Page(void){

    char goodsID[MAX_ID_LEN],idwarehouse[MAX_ID_LEN];
    
    int quantity;
    int mode;

                printf("\nChoose a sorting option:\n");
                printf("1. Remove manually\n");
                printf("2. Remove using .csv file\n");
                scanf("%d", &mode);

    switch (mode) {
        case 1:
            printf("Please enter the warehouse ID :");
            scanf("%s",idwarehouse);
            printf("Please enter the goods ID :");
            scanf("%s",goodsID);
            printf("Please enter the quantity :");
            scanf("%d",&quantity);
            //make this function reduce goods in warehouse like a throw garbage to trashcan
            if (removeGOODSFromWarehouse(idwarehouse,"inventory",goodsID,quantity)){
                printf("Goods removed successfully\n");
            }
        break;
        
    case 2:

    if (removeGOODSFromWarehouseUsingFile("back/warehouse/1/remove-list.csv")) {
        printf("All items processed successfully.\n");
    }

    break;
    
    default:
        printf("Invalid choice.\n");
        break;
            }
        }