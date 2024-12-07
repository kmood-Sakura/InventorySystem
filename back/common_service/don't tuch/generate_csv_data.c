#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "generater_service.h"


#define filetype "csv"

int get_last_id(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return -1;
    }

    char line[256];
    int last_id = 0;
    
    // Skip header line
    fgets(line, sizeof(line), file);
    
    // Read all lines to find the last one
    while (fgets(line, sizeof(line), file) != NULL) {
        int current_id;
        sscanf(line, "%d", &current_id);
        if (current_id > last_id) {
            last_id = current_id;
        }
    }

    fclose(file);
    return last_id;
}

void generate_item_data( const char* data_directory, const char* filename, int additional_records) {

    char* filepath = create_current_path(filename,data_directory,filetype);
    
    // Get the last ID from the file
    int last_id = get_last_id(filepath);
    if (last_id < 0) {
        return;
    }
    
    int start_from = last_id + 1;
    
    FILE* file = fopen(filepath, "a");
    if (file == NULL) {
        printf("Error opening file for appending!\n");
        return;
    }

    int end_number = start_from + additional_records - 1;
    
    // Generate additional records
    for (int i = start_from; i <= end_number; i++) {
        // Create ID with leading zeros
        char id[6];
        sprintf(id, "%05d", i);
        
        // Create object name
        char obj_name[5];
        sprintf(obj_name, "ob%d", i);
        
        // Create description
        char description[7];
        sprintf(description, "none%d", i);
        
        // Calculate price (starts from 10.1 and increments by 0.1)
        float price = 10.0 + (i * 0.1);
        
        // Write to file
        fprintf(file, "%s,%s,%s,%.1f,%d\n", 
                id, obj_name, description, price, i);
    }

    fclose(file);
    printf("Added %d records (from %05d to %05d) to %s\n", 
           additional_records, start_from, end_number, filepath);
}

void generate_user_data(const char* data_directory, const char* filename, int additional_records){
    
    char* filepath = create_current_path(data_directory,filename,filetype);

    int last_id = get_last_id(filepath);
    if (last_id < 0) {
        printf("can't find the last id\n");
        return;
    }
    int start_from = last_id + 1;
    
    FILE* file = fopen(filepath, "a");
    if (file == NULL) {
        printf("Error opening file for appending!\n");
        return;
    }

    int end_number = start_from + additional_records - 1;
    // Generate additional records
    for (int i = start_from; i <= end_number; i++) {
        // Create ID with leading zeros
        char id[6];
        sprintf(id, "%05d", i);
        
        // Create object name
        char name[5];
        sprintf(name, "ob%d", i);
        
        // Create email
        char email[14];
        sprintf(email, "p%d@gmail.com", i);
        
        char phone[10];
        sprintf(phone, "%09d", i);
        // Calculate price (starts from 10.1 and increments by 0.1)
        char password[6];
        sprintf(password, "psw%d", i);
        
        // Write to file
        fprintf(file, "%s,%s,%s,%s,%s\n", 
                id, name, email, phone, password);
    }

    fclose(file);
    printf("Added %d records (from %05d to %05d) to %s\n", 
           additional_records, start_from, end_number, filepath);
}