#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../get_goods_data_service.h"

// Function to parse one CSV line into a GOODS struct
int parseGOODSCSVLine(char *line, GOODS *item) {
    char *token;
    int field = 0;
    
    // Skip empty lines
    if (strlen(line) <= 1) return 0;
    
    // Remove newline character if present
    line[strcspn(line, "\n")] = 0;
    
    // Get first token (ID)
    token = strtok(line, ",");
    while (token != NULL && field < 5) {  // 5 fields in GOODS struct
        // Remove quotes if present
        if (token[0] == '"') {
            token++;
            token[strlen(token)-1] = '\0';
        }
        
        switch(field) {
            case 0:  // ID
                strncpy(item->id, token, MAX_ID_LEN - 1);
                item->id[MAX_ID_LEN - 1] = '\0';
                break;
            case 1:  // Name
                strncpy(item->name, token, MAX_GOODS_NAME_LEN - 1);
                item->name[MAX_GOODS_NAME_LEN - 1] = '\0';
                break;
            case 2:  // Description
                strncpy(item->description, token, MAX_DESC_LEN - 1);
                item->description[MAX_DESC_LEN - 1] = '\0';
                break;
            case 3:  // Price
                item->price = atof(token);
                break;
            case 4:  // quantity
                item->quantity = atoi(token);
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    
    return (field == 5) ? 1 : 0;  // Return 1 if all fields were read
}

GOODS* getGOODSCSVpath(const char* filepath, int* itemCount){
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    GOODS *items = NULL;
    int capacity = 10;  // Initial capacity
    *itemCount = 0;

    items = (GOODS*)malloc(capacity * sizeof(GOODS));
    if (items == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_GOODS_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*itemCount >= capacity) {
            capacity *= 2;
            GOODS *temp = realloc(items, capacity * sizeof(GOODS));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(items);
                fclose(file);
                return NULL;
            }
            items = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d", 
               items[*itemCount].id, 
               items[*itemCount].name, 
               items[*itemCount].description, 
               &items[*itemCount].price, 
               &items[*itemCount].quantity);
        
        (*itemCount)++;
    }

    fclose(file);
    return items;
}
GOODS* getGOODSCSV(const char *filename, int *itemCount) {

    char *filepath = create_current_path("back/database/", filename, "csv");
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    GOODS *items = NULL;
    int capacity = 10;  // Initial capacity
    *itemCount = 0;

    items = (GOODS*)malloc(capacity * sizeof(GOODS));
    if (items == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_GOODS_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*itemCount >= capacity) {
            capacity *= 2;
            GOODS *temp = realloc(items, capacity * sizeof(GOODS));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(items);
                fclose(file);
                return NULL;
            }
            items = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d", 
               items[*itemCount].id, 
               items[*itemCount].name, 
               items[*itemCount].description, 
               &items[*itemCount].price, 
               &items[*itemCount].quantity);
        
        (*itemCount)++;
    }

    fclose(file);
    return items;
}

int showALLGOODS(GOODS* goods, int itemCount){
    for(int i=0;i<itemCount;i++){
        printGOODS(&goods[i]);
    }
    return 1;
}
// Function to print GOODS for verification
int printGOODS(const GOODS *item) {
    printf("ID: %d\n", item->id);
    printf("Name: %s\n", item->name);
    printf("Description: %s\n", item->description);
    printf("Price: %.2f\n", item->price);
    printf("quantity: %d\n", item->quantity);
    printf("------------------------\n");
    return 1;
}
