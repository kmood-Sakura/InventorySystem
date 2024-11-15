#include "handler.h"

#define MAX_LINE_LENGTH 1024

// Function to count lines in file (excluding header)
int countCSVLines(const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return -1;
    }
    
    int lines = -1;  // Start at -1 to exclude header
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    
    fclose(file);
    return (lines < 0) ? 0 : lines;
}

// Function to parse one CSV line into a Goods struct
int parseCSVLine(char *line, Goods *item) {
    char *token;
    int field = 0;
    
    // Skip empty lines
    if (strlen(line) <= 1) return 0;
    
    // Remove newline character if present
    line[strcspn(line, "\n")] = 0;
    
    // Get first token (ID)
    token = strtok(line, ",");
    while (token != NULL && field < 5) {  // 5 fields in Goods struct
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
                strncpy(item->name, token, MAX_NAME_LEN - 1);
                item->name[MAX_NAME_LEN - 1] = '\0';
                break;
            case 2:  // Description
                strncpy(item->description, token, MAX_DESC_LEN - 1);
                item->description[MAX_DESC_LEN - 1] = '\0';
                break;
            case 3:  // Price
                item->price = atof(token);
                break;
            case 4:  // Stock
                item->stock = atoi(token);
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    
    return (field == 5) ? 1 : 0;  // Return 1 if all fields were read
}

// Function to read CSV file into array of Goods
Goods* readCSVfile(const char *filename, int *itemCount) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    // Count lines first
    *itemCount = countCSVLines(filename);
    if (*itemCount <= 0) {
        fprintf(stderr, "Error: No data in file or file is empty\n");
        return NULL;
    }
    
    // Allocate memory for all items
    Goods *items = (Goods*)malloc(*itemCount * sizeof(Goods));
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
    
    char line[MAX_LINE_LENGTH];
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
        items = realloc(items, currentItem * sizeof(Goods));
    }
    
    return items;
}

// Function to print Goods for verification
void printGoods(const Goods *item) {
    printf("ID: %d\n", item->id);
    printf("Name: %s\n", item->name);
    printf("Description: %s\n", item->description);
    printf("Price: %.2f\n", item->price);
    printf("Stock: %d\n", item->stock);
    printf("------------------------\n");
}