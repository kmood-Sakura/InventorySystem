#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../update_file_service.h"

int update_item_quantity(const char* directory, const char* filename, const char* item_id, int quantity_change) {

    char *filepath = create_current_path(directory,filename,"csv");
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[MAX_LINE_DATA_LEN];
    char *temp_filepath = create_allocate_path(directory,"temp","csv");
    FILE *temp = fopen(temp_filepath, "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return 0;
    }

    int updated = 0;
    // Copy header
    if (fgets(line, MAX_GOODS_DATA_LEN, file) != NULL) {
        fputs(line, temp);
    }

    while (fgets(line, MAX_GOODS_DATA_LEN, file) != NULL) {
        char id[MAX_ID_LEN];
        char name[MAX_GOODS_NAME_LEN];
        char description[MAX_DESC_LEN];
        float price;
        int quantity;

        line[strcspn(line, "\n")] = 0;  // Remove newline
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d", id, name, description, &price, &quantity);
        
        if (strcmp(id, item_id) == 0) {
            int new_quantity = quantity + quantity_change;
            if (new_quantity < 0) {
                printf("Error: Quantity cannot be negative.\n");
                fclose(file);
                fclose(temp);
                remove(temp_filepath);
                return 0;
            }
            fprintf(temp, "%s,%s,%s,%.2f,%d\n", id, name, description, price, new_quantity);
            updated = 1;
        } else {
            fprintf(temp, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (updated) {
        remove(filepath);
        rename(temp_filepath, filepath);
        free(temp_filepath);
        return 1;  // Success
    } else {
        remove(temp_filepath);
        free(temp_filepath);
        printf("Item with ID %s not found.\n", item_id);
        return 0;  // Failure
    }
}