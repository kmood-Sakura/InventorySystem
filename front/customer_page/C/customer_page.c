#include <stdio.h>
#include <stdlib.h>

#include "../customer_page.h"

void Customer_Page(void){

    printf("Command Choice\nO : order\nS : Search\nE : Exit\nA : Access Owner Page\n");
    while(1){
        char key;
        printf("system command : ");
        scanf(" %c",&key);
        switch (key){
            case 'O': Order_Page();
                break;
            case 'S': Search_Goods_Page();
                break;
            case 'E': exit(1);
            case 'A': //Access_Owner_Page();
                break;
            default:
                printf("Invalid Key Command. Please Enter Again\n");
                break;
        }
    }
}