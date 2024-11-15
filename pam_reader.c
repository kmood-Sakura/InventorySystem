#include "handler/handler.h"

int main(){
    int line;
    char filename[] = "tempTest_pam.csv";

    Goods *dataReaded = readCSVfile(filename,&line); 

    //!!this function will count line for us. just sent the position of integer variable!!

    printf("data id : %s\n",dataReaded->id);
    printf("data have %d line\n",line);
    return 0;
}