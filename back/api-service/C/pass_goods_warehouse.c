#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pass_goods_warehouse.h"
#define MAX_LINE_LENGTH 256

int addGOODSToWarehouse(const char* warehouse_name,const char* main_warehouse_name,const char* filename, const char* goodsID, int quantity){
    char *maindir = create_allocate_dir("back/warehouse/",main_warehouse_name);
    if(!update_item_quantity(maindir,filename,goodsID,-quantity)){
        printf("Error : not enough item in inventory\n");

        free(maindir);  
        
        return 0;
    }

    char *destinationdir = create_allocate_dir("back/warehouse/",warehouse_name);
    if(!update_item_quantity(destinationdir,filename,goodsID,quantity)){
        printf("Error : Can't update to destination warehouse\n");
        free(destinationdir);
        free(maindir);
        return 0;
    }
        free(destinationdir);
        free(maindir);

    return 1;
}


int removeGOODSFromWarehouse(const char* warehouse_name,const char* filename, const char* goodsID, int quantity) {
    char *maindir = create_allocate_dir("back/warehouse/",warehouse_name);
    if(!update_item_quantity(maindir,filename,goodsID,-quantity)){
        printf("Error : not enough item in inventory\n");
        free(maindir);
        return 0;
    }
    free(maindir);
    return 1;
}

int removeGOODSFromWarehouseUsingFile(const char* csv_filepath) {
    FILE *file = fopen(csv_filepath, "r");
    if (!file) {
        printf("Error: Unable to open the CSV file %s\n", csv_filepath);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char warehouse_name[MAX_LINE_LENGTH];
        char filename[MAX_LINE_LENGTH];
        char goodsID[MAX_LINE_LENGTH];
        int quantity;

        if (sscanf(line, "%255[^,],%255[^,],%255[^,],%d", warehouse_name, filename, goodsID, &quantity) == 4) {
        
            printf("Processing: Warehouse: %s, File: %s, Goods ID: %s, Quantity: %d\n", warehouse_name, filename, goodsID, quantity);
            if (!removeGOODSFromWarehouse(warehouse_name, filename, goodsID, quantity)) {
                printf("Failed to remove goods from warehouse: %s\n", warehouse_name);
                fclose(file);
                return 0;
            }
        } else {
            printf("Error: Invalid line format in CSV: %s\n", line);
        }
    }

    fclose(file);
    return 1;
}

int addGoodsToWarehouseFromFile(const char* subwarehouseID, const char *main_warehouseID) {
    //const char* warehouse_name;           // Destination warehouse.
    const char* filepath = create_full_path("back/warehouse/",subwarehouseID,"/transfer","csv");
            // Inventory file.
    printf("path add file : %s\n",filepath);
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Error: Unable to open CSV file: %s\n", filepath);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int success = 1; // Track if all operations were successful.
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char goodsID[MAX_LINE_LENGTH];
        int quantity;

        // Parse the line into goodsID and quantity.
        if (sscanf(line, "%[^,],%d", goodsID, &quantity) == 2) {
            // Call addGOODSToWarehouse for each item.
            if (!addGOODSToWarehouse(subwarehouseID, main_warehouseID, "inventory", goodsID, quantity)) {
                printf("Error: Failed to process goodsID: %s\n", goodsID);
                success = 0; // Mark failure, but continue processing remaining lines.
            }
        } else {
            printf("Transfer successfully\n");
            success = 0; // Mark failure for invalid format.
        }
    }

    fclose(file);
    return success;
    return 1;
}