#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../get_OWNER_data_service.h"


OWNER* getOWNERCSVpath(const char* filepath, int* ownerCount){
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    OWNER *owners = NULL;
    int capacity = 10;  // Initial capacity
    *ownerCount = 0;

    owners = (OWNER*)malloc(capacity * sizeof(OWNER));
    if (owners == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_OWNER_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*ownerCount >= capacity) {
            capacity *= 2;
            OWNER *temp = realloc(owners, capacity * sizeof(OWNER));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(owners);
                fclose(file);
                return NULL;
            }
            owners = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%s", 
               owners[*ownerCount].warehouseid, 
               owners[*ownerCount].id, 
               owners[*ownerCount].token, 
               owners[*ownerCount].name);
        
        (*ownerCount)++;
    }

    fclose(file);
    return owners;
}

OWNER* getOWNERCSV(const char* directory, const char *filename, int *ownerCount) {

    char *filepath = create_current_path(directory, filename, "csv");
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    OWNER *owners = NULL;
    int capacity = 10;  // Initial capacity
    *ownerCount = 0;

    owners = (OWNER*)malloc(capacity * sizeof(OWNER));
    if (owners == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char line[MAX_OWNER_DATA_LEN];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (*ownerCount >= capacity) {
            capacity *= 2;
            OWNER *temp = realloc(owners, capacity * sizeof(OWNER));
            if (temp == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(owners);
                fclose(file);
                return NULL;
            }
            owners = temp;
        }

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%s", 
               owners[*ownerCount].warehouseid, 
               owners[*ownerCount].id, 
               owners[*ownerCount].token, 
               owners[*ownerCount].name);
        
        (*ownerCount)++;
    }

    fclose(file);
    return owners;
}

// Function to print OWNER for verification
void printOWNER(const OWNER *owner) {
    printf("WarehouseID: %s",owner->warehouseid);
    printf("ID: %s\n", owner->id);
    printf("Token: %s\n", owner->token);
    printf("Name: %s\n", owner->name);
    printf("------------------------\n");
}

int showALLOWNER(OWNER* owners, int ownerCount){
    for(int i=0;i<ownerCount;i++){
        printOWNER(&owners[i]);
    }
    return 0;
}