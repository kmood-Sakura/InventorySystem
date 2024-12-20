#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../write_file_service.h"

void writeCSVrows(const char* data_directory, const char *filename, const GOODS *data, int count) {

    char *filepath = create_current_path(data_directory, filename, "csv");
    
    FILE *file = fopen(filepath, "a");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return;
    }
    
    // Write data for the specified count
    for (int i = 0; i < count; i++) {
        // Buffer for handling escaped strings
        char name_escaped[MAX_GOODS_NAME_LEN * 2];
        char desc_escaped[MAX_GOODS_NAME_LEN * 2];
        
        // Escape name if it contains commas or quotes
        if (strchr(data[i].name, ',') != NULL || strchr(data[i].name, '"') != NULL) {
            snprintf(name_escaped, sizeof(name_escaped), "\"%s\"", data[i].name);
        } else {
            snprintf(name_escaped, sizeof(name_escaped), "%s", data[i].name);
        }
        
        // Escape description if it contains commas or quotes
        if (strchr(data[i].description, ',') != NULL || strchr(data[i].description, '"') != NULL) {
            snprintf(desc_escaped, sizeof(desc_escaped), "\"%s\"", data[i].description);
        } else {
            snprintf(desc_escaped, sizeof(desc_escaped), "%s", data[i].description);
        }
        
        // Write the data in CSV format
        fprintf(file, "%d,%s,%s,%.2lf,%d\n",
                data[i].id,
                name_escaped,
                desc_escaped,
                data[i].price,
                data[i].quantity);
    }
    
    fclose(file);
}