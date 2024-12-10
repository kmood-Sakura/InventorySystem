#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../create_file_service.h"

int createFile(const char* data_directory,const char *filename,const char* filetype){
    char *filepath = create_current_path(data_directory, filename, filetype);
    if(fileExists(filepath)){
        printf("file ('%s') already exist\n",filepath);
        return -1;
    }
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filepath);
        return 1;
    }
}

int createFilePath(const char* filepath){
    if(fileExists(filepath)){
        printf("file ('%s') already exist\n",filepath);
        return -1;
    }
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filepath);
        return 1;
    }
}

// Function to create CSV file with custom headers
int createCSVfile(const char *filename, const char *headers) {
    char *filepath = create_current_path("back/database/", filename,"csv");
    
    if(fileExists(filepath)){
        printf("file ('%s') already exist\n",filepath);
        return -1;
    }
    // Try to open file
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create this csv file ('%s')\n", filepath);
        return 0;
    }
    
    // Write headers
    fprintf(file, "%s\n", headers);
    
    fclose(file);
    printf("CSV file '%s' created successfully with headers: %s\n", filepath, headers);
    return 1;
}


// Helper function to validate if file exists
//int fileExists(const char* data_directory, const char *filename, const char* filetype) 
int fileExists(const char* filepath){
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}