#ifndef GENERATER_H
#define GENERATER_H

#define MAX_PATH 400

#include "../create_file_service.h"
//void generater_struct_service();
void generate_headerfile(const char* path_directory, const char* filename);

//void generater_service();
int get_last_id(const char* filepath);
void generate_item_data( const char* data_directory, const char* filename, int additional_records);
void generate_item_data(const char* data_directory, const char* filename, int additional_records);

#endif