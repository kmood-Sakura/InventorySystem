#include <stdio.h>

#include "../add_page.h"



void Add_Page(void){
    char goodsID[MAX_ID_LEN],idwarehouse[MAX_ID_LEN];
    char warehouse_name[MAX_ID_LEN];
    char csv_filename[MAX_ID_LEN];
    const char* csvFilePath = "back/warehouse/1/transfer.csv";
    int  quantity;
    int  mode;
        const char* destination_warehouse = "warehouse_2"; 
        const char* main_warehouse = "main_warehouse"; 
                printf("\nChoose a sorting option:\n");
                printf("1. Add manually\n");
                printf("2. Add using .csv file\n");
                scanf("%d", &mode);

switch (mode) {
                case 1:
                        printf("Please enter the warehouse ID :");
                        scanf("%s",idwarehouse);

                        printf("Please enter the goods ID :");
                        scanf("%s",goodsID);

                            printf("Please enter the quantity :");
                            scanf("%d",&quantity);
                    //use this function
                            if(addGOODSToWarehouse(idwarehouse,"main","inventory",goodsID,quantity)){
                            printf("Goods transfer successfully\n");
                            }
                            break;
                case 2:

                        if (addGoodsToWarehouseFromFile(csvFilePath)) {
                        printf("All items were successfully transferred to the warehouse.\n");
                }  
                break;

                default:
                        printf("Invalid choice.\n");
                        break;
        
        }
}