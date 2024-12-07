#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generater_service.h"

//#include <errno.h>

void generate_headerfile(const char* path_directory, const char* filename) {
   
    // Create header filepath
    char filetype[] = "h";
    char *filepath = create_current_path(path_directory, filename, filetype);
    if (filepath == NULL) {
        printf("Failed to create filepath\n");
        return;
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create file %s\n", filepath);
        free(filepath);
        return;
    }

    // Convert filename to uppercase for header guard
    char *header = strdup(filename);
    if (header == NULL) {
        fclose(file);
        free(filepath);
        return;
    }
    
    for (int i = 0; header[i]; i++) {
        header[i] = toupper(header[i]);
    }

    // Write header guard and content
    fprintf(file, "#ifndef %s_H\n", header);
    fprintf(file, "#define %s_H\n\n", header);
    //fprintf(file, "#define MAX_%s_LEN 50\n\n", header);
    fprintf(file, "#endif /* %s_H */\n", header);

    fclose(file);
    free(header);
    free(filepath);
    printf("File '%s' created successfully\n", filepath);
}

