#include "search_data_service.h"

// Function to parse one CSV line into a Goods struct
int parseCSVLinebyFilter(char *line, Goods *item, userFilter *reqUserFilter) {
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
                if (FilterbyPrice(reqUserFilter, item) == 0) {
                    return 0;  // Filter didn't match, but data was parsed correctly
                }
                break;
            case 4:  // Stock
                item->stock = atoi(token);
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }
    
    return (field == 5) ? 1 : -1;  // Return 1 if all fields were read, -1 if parsing failed
}

// Function to read CSV file into array of Goods
Goods* searchCSVfile(const char *filename, int *itemCount, userFilter *reqUserFilter) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    
    // Count lines first
    //*itemCount = countCSVLines(filename);
    if (countCSVLines(filename) <= 0) {
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
    while (fgets(line, sizeof(line), file)) {
        if (parseCSVLinebyFilter(line, &items[currentItem], reqUserFilter) == 1) {
            // Successfully parsed and passed filter
            currentItem++;
            //printf("item %d\n",currentItem);
            //if (currentItem >= *itemCount) break;
        }
        /*
        else if (parseResult == -1) {
            // Parse error
            fprintf(stderr, "Error: Failed to parse line for item %d\n", currentItem + 1);
        }*/
        // If parseResult == 0, it means filter didn't match, so continue to next line
    }
    *itemCount = currentItem;
    
    fclose(file);
    
    /*
    if (currentItem < *itemCount) {
        // Adjust count to actual number of items read
        *itemCount = currentItem;
        if (currentItem > 0) {
            Goods *resized = realloc(items, currentItem * sizeof(Goods));
            if (resized != NULL) {
                items = resized;
            }
        }
    }*/
    
    return items;
}

int FilterbyPrice(userFilter *reqUserFilter, Goods *item) {
    if (!reqUserFilter || !item) return 1;  // No filter means accept all
    const double price = (double)item->price;
    //printf("filter : %.2lf, %c\n",reqUserFilter->price,reqUserFilter->condition_price);
    switch (reqUserFilter->condition_price) {
        case '=': return (price == reqUserFilter->price) ? 1 : 0;
        case '<': return (price <= reqUserFilter->price) ? 1 : 0;
        case '>': return (price >= reqUserFilter->price) ? 1 : 0;
        default:
            fprintf(stderr, "Error: invalid filter price condition\n");
            return 0;
    }
}