#ifndef PATH_H
#define PATH_H

#define MAX_MY_PATH 200
#define MAX_FILENAME_LEN 30
#define MAX_DIR_LEN 100

char* create_full_path(const char* filename,const char *directory_path);
char* create_current_path(const char *directory_path, const char* filename,const char* filetype);
char* create_current_directory(const char* current_working_directory,const char *directory_path);
char* create_allocate_path(const char *directory_path, const char* filename,const char* filetype);
char* create_allocate_dir(const char* directory,const char* directTo);

#endif