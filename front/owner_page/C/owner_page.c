#include <stdio.h>
#include <stdlib.h>

#include "../owner_page.h"

void Owner_Page(void){
    while(1){
        char key;
        printf("system command : ");
        scanf(" %c",&key);
        switch (key){
            case 'O': Apply_Order_Page();
                break;
            case 'S': Search_Warehouse_Inventory();
                break;
            case '+': Add_Page();
                break;
            case '-': Minus_Page();
                break;
            case 'E': exit(200);
            case 'A': //Access_Owner_Page();
                break;
            default:
                printf("Invalid Key Command. Please Enter Again\n");
                break;
        }
    }
}