#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../book_page.h"

void Book_Page(void) {
    printf("start Amzalgo\n");

    // Dynamically allocate memory for GOODS structure
    GOODS* temp = (GOODS*)malloc(sizeof(GOODS));
    if (temp == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    // Initialize GOODS structure
    strcpy(temp->id, "00001");
    strcpy(temp->name, "temp1");
    strcpy(temp->description, "maitongsaikodai");
    temp->price = 10.9;
    temp->quantity = 1;

    // Call AMZ function
    AMZ(temp);

    // Free allocated memory
    free(temp);
}
