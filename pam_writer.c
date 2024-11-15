#include "handler/handler.h"

int main(){
    char goodsHeader[] = "id,name,description,price,stonk"; //same header to handle inventory system!!!!!
    char filename[] = "tempTest_pam.csv";
    createCSVifNotExists(filename,goodsHeader);
    Goods data[5] = {
        {"B1","pam","no des",10,0},
        {"B2","pam2","no des",10,0},
        {"B3","pam3","no des",10,0},
        {"B4","pam4","no des",10,0},
        {"B5","pam5","no des",10,0}
    };
    printf("start creating");
    writeCSVrows(filename,data,5);
    return 0;
}