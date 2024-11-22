#include "create_file.h"

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