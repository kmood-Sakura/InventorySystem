#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../path_service.h"

char *create_allocate_path(const char *directory_path, const char* filename,const char* filetype){
    char *full_path = (char*)malloc(MAX_MY_PATH * sizeof(char));
    if (full_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL; // Handle allocation failure (return NULL to indicate error)
    }
    snprintf(full_path, MAX_MY_PATH, "%s%s.%s", directory_path, filename,filetype);
    return full_path;
}

char* create_allocate_dir(const char* directory,const char* directTo){
    char *dir = (char*)malloc(MAX_MY_PATH * sizeof(char));
    if (dir == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL; // Handle allocation failure (return NULL to indicate error)
    }
    snprintf(dir, MAX_MY_PATH, "%s%s/", directory, directTo);
    return dir;
}

char* create_file_path(const char *directory_path,const char* filename) {
    static char filepath[MAX_MY_PATH];
    snprintf(filepath, MAX_MY_PATH, "%s%s",directory_path, filename);
    return filepath;
}

char* create_current_path(const char *directory_path, const char* filename,const char* filetype) {
    static char full_path[MAX_MY_PATH];
    snprintf(full_path, MAX_MY_PATH, "%s%s.%s", directory_path, filename,filetype);
    return full_path;
}

char* create_current_directory(const char* current_working_directory,const char *directory_path) {
    static char full_path[MAX_MY_PATH];
    snprintf(full_path, MAX_MY_PATH, "%s%s/",current_working_directory, directory_path);
    return full_path;
}

void direct_to_path(const char* dir_path){
    chdir(dir_path);
    printf("you success fully direct to %s path\n",dir_path);
}