#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../amazon_algo.h"

int loadWarehouseData(WAREHOUSE* data, char *id) {
    char *path = create_full_path("back/warehouse/", id, "/order", "csv");
    int itemCount;
    GOODS* allitems = getGOODSCSVpath(path, &itemCount);
    
    if (allitems == NULL) {
        free(path);
        return 0;
    }

    // Copy the warehouse ID
    strncpy(data->id, id, MAX_ID_LEN - 1);
    data->id[MAX_ID_LEN - 1] = '\0'; // Ensure null-termination

    // Copy goods data
    data->goods_count = (itemCount < MAX_GOODS) ? itemCount : MAX_GOODS;
    for (int i = 0; i < data->goods_count; i++) {
        data->goods[i] = allitems[i];
    }

    // Free the temporary allitems array
    free(allitems);
    free(path);
    return 1;
}
int loadAllWarehouseData(DATA * allData, const char* id_main) {
    char *path_main = create_full_path("back/warehouse/", id_main, "/subwarehouse", "csv");
    FILE *file = fopen(path_main, "r");
    if (!file) {
        perror("Error: Can't open file");
        free(path_main);
        return 0;
    }

    allData->warehouse_count = 0;
    char line[MAX_ID_LEN * MAX_WAREHOUSES];
    
    while (fgets(line, sizeof(line), file) && allData->warehouse_count < MAX_WAREHOUSES) {
        char *id = strtok(line, ",");
        if (id) {
            id[strcspn(id, "\n")] = 0; // Remove newline if present
            if (loadWarehouseData(&allData->warehouses[allData->warehouse_count], id)) {
                allData->warehouse_count++;
            }
        }
    }

    fclose(file);
    free(path_main);
    return allData->warehouse_count > 0;
}

int Amazon_Algo(const char* id) {
    DATA* orderdata = (DATA*)malloc(sizeof(DATA));
    if (orderdata == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    if (!loadAllWarehouseData(orderdata, id)) {
        printf("Failed to load warehouse data\n");
        free(orderdata);
        return 0;
    }

    // Create an array of TempInfo to store max quantities for each goods ID
    TempInfo tempInfoArray[MAX_GOODS];
    int tempInfoCount = 0;

    printf("count : %d\n",orderdata->warehouse_count);
    // Loop through all warehouses to get max quantities
    for (int i = 0; i < orderdata->warehouse_count; i++) {
        WAREHOUSE* warehouse = &orderdata->warehouses[i];
        for (int j = 0; j < warehouse->goods_count; j++) {
            GOODS* item = &warehouse->goods[j];
            
            // Check if this goods ID is already in tempInfoArray
            int found = 0;
            for (int k = 0; k < tempInfoCount; k++) {
                if (strcmp(tempInfoArray[k].id, item->id) == 0) {
                    tempInfoArray[k].maxQuantity += item->quantity;
                    found = 1;
                    break;
                }
            }

            // If not found, add to tempInfoArray
            if (!found && tempInfoCount < MAX_GOODS) {
                strcpy(tempInfoArray[tempInfoCount].id, item->id);
                tempInfoArray[tempInfoCount].maxQuantity = item->quantity;
                tempInfoCount++;
            }
        }
    }

    // Create updated stock files for each warehouse
    for (int i = 0; i < orderdata->warehouse_count; i++) {
        WAREHOUSE* warehouse = &orderdata->warehouses[i];
        if (!create_updated_stock(tempInfoArray, tempInfoCount, warehouse)) {
            printf("Failed to create updated stock file for warehouse %s\n", warehouse->id);
        }
    }
    char mainP[] = "back/warehouse/main/inventory.csv";
    char tempMain[] = "back/warehouse/main/temper.csv";
    FILE *mainF = fopen(tempMain,"w");
    if(mainF){
        fprintf(mainF,"%s\n",HEADER);
        remove(mainP);
        rename(tempMain,mainP);
        return 0;
    }
    free(orderdata);
    return 1;
}

int create_updated_stock(TempInfo *information, int infoCount, WAREHOUSE* warehouse) {
    // Create the file path
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "back/warehouse/%s/transfer.csv", warehouse->id);

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return 0;
    }

    // Write the header
    fprintf(file, "id,percent\n");

    // Loop through all goods in the warehouse
    for (int i = 0; i < warehouse->goods_count; i++) {
        GOODS* item = &warehouse->goods[i];
        double percent = 0.0;
        int quantity;
        int mainCount;
        GOODS* main = getGOODSCSVpath("back/warehouse/main/inventory.csv",&mainCount);
        // Find the max quantity for this item
        for (int j = 0; j < infoCount; j++) {
            if (strcmp(information[j].id, item->id) == 0) {
                if (information[j].maxQuantity > 0) {
                    int maxQ = 0;
                    //printf("quantity : %d, max : %d\n",item->quantity,information[j].maxQuantity);
                    percent = (double)item->quantity / information[j].maxQuantity;
                    for(int o=0;o<mainCount;o++){
                        if(strcmp(main[o].id,information->id)==0){
                            maxQ = main[o].quantity;
                            break;
                        }
                    }
                    quantity = percent*maxQ;
                }
                break;
            }
        }

        // Write the item id and percent to the file
        fprintf(file, "%s,%d\n", item->id, quantity);
    }

    // Close the file
    fclose(file);
    printf("Updated stock file created: %s\n", filepath);
    return 1;
}


