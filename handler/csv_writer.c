#include "handler.h"

// Function to create CSV file with custom headers
void createCSVfile(const char *filename, const char *headers) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    // Try to open file
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filepath);
        return;
    }
    
    // Write headers
    fprintf(file, "%s\n", headers);
    
    fclose(file);
    printf("CSV file '%s' created successfully with headers: %s\n", filepath, headers);
}

// Function to create CSV file with headers if it doesn't exist
void createCSVifNotExists(const char *filename, const char *headers) {
    if (!fileExists(filename)) {
        createCSVfile(filename, headers);
    } else {
        printf("File '%s' already exists. Skipping creation.\n", filename);
    }
}
// Helper function to validate if file exists
int fileExists(const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void writeCSVrows(const char *filename, const Goods *data, int count) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    FILE *file = fopen(filepath, "a");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return;
    }
    
    // Write data for the specified count
    for (int i = 0; i < count; i++) {
        // Buffer for handling escaped strings
        char name_escaped[MAX_NAME_LEN * 2];
        char desc_escaped[MAX_DESC_LEN * 2];
        
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
        fprintf(file, "%d,%s,%s,%.2f,%d\n",
                data[i].id,
                name_escaped,
                desc_escaped,
                data[i].price,
                data[i].stock);
    }
    
    fclose(file);
}