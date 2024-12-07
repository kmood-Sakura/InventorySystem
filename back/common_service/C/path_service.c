#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../path_service.h"

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

char* create_warehouse_dir(const char *directory_path, const char* warehouse_name) {
    static char full_path[MAX_MY_PATH];
    snprintf(full_path, MAX_MY_PATH, "%s%s/", directory_path,warehouse_name);
    return full_path;
}

char* create_current_directory(const char* current_working_directory,const char *directory_path) {
    static char full_path[MAX_MY_PATH];
    snprintf(full_path, MAX_MY_PATH, "%s%s",current_working_directory, directory_path);
    return full_path;
}

void direct_to_path(const char* dir_path){
    chdir(dir_path);
    printf("you success fully direct to %s path\n",dir_path);
}