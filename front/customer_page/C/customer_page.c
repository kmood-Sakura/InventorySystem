#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../customer_page.h"

void Customer_Page(void){
    printf("Command Choice\no : Order\ns : Search\ne : Exit\na : Access Owner Page\n");
    while(1) {
        char key;
        printf("\n");
        printf("system command: ");
        scanf(" %c",&key);
        
        key = toupper(key);

        switch (key){
            case 'O': Order_Page(); break;
            case 'S': Search_Goods_Page(); break;
            case 'E': exit(1);
            case 'A': Access_Owner_Page(); break;
            default: 
                printf("\n");
                printf("Invalid Key Command. Please Enter Again\n"); 
                printf("\n");
                printf("--------------------------------------------------------\n");
                break;
        }
    }
}