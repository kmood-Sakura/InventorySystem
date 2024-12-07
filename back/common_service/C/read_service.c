#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../read_file_service.h"

#define MAX_DATA_LINE 1024

FILE* readFile(const char* filepath){
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return NULL;
    }
    return file;
}

int countCSVLines(FILE* csvfile) {
    int lines = -1;  // Start at -1 to exclude header
    char ch;
    while ((ch = fgetc(csvfile)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    
    fclose(csvfile);
    return (lines < 0) ? 0 : lines;
}




/*
GOODS* readCSVfileOld(const char *filename, int *itemCount, const char* data_directory) {

    char *filepath = create_current_path(data_directory, filename, "csv");
    
    // Count lines first
    *itemCount = countCSVLines(filepath);
    if (*itemCount <= 0) {
        fprintf(stderr, "Error: No data in file or file is empty\n");
        return NULL;
    }
    
    // Allocate memory for all items
    GOODS *items = (GOODS*)malloc(*itemCount * sizeof(GOODS));
    if (items == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    // Open file for reading
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        free(items);
        return NULL;
    }
    
    char line[MAX_LINE_DATA_LEN];
    int currentItem = 0;
    
    // Skip header line
    fgets(line, sizeof(line), file);
    
    // Read data lines
    while (fgets(line, sizeof(line), file) && currentItem < *itemCount) {
        if (parseCSVLine(line, &items[currentItem])) {
            currentItem++;
        }
    }
    
    fclose(file);
    
    if (currentItem != *itemCount) {
        // Adjust count if some lines were invalid
        *itemCount = currentItem;
        items = realloc(items, currentItem * sizeof(GOODS));
    }
    
    return items;
}
*/