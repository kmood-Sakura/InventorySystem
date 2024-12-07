#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../search_goods_page.h"

void Search_Goods_Page(void){
    //(*) = select all
    //filter by name
    printf("search for goods\n");
    //Atip

    //get name goods

    //search all item that is the same name

    //show all the result

}

int showALLGOODS(GOODS* items, int itemCount){
    for(int i=0;i<itemCount;i++){
        printGOODS(&items[i]);
    }
    return 0;
}

//use this function to show all 
void Search_Common_Page(void){
    int itemCount;
    GOODS* items = getGOODSCSV("inventory", &itemCount); 
    showALLGOODS(items, itemCount);
}