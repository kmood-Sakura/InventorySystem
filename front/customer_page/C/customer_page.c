#include <stdio.h>
#include <stdlib.h>

#include "../customer_page.h"

void Customer_Page(AUTH *auth){
    if(!auth->customer){
        if(!Begin_Access(auth)){
            return;
        }
    }
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
            case 'E': 
                printf("Exiting the system. Goodbye!\n");
                exit(200);
            case 'A': return Owner_Page(auth);
            case 'B': 
                if(auth->owner){
                    return Owner_Page(auth);
                }break;
            default:
                printf("Invalid Key Command. Please Enter Again\n");
                break;
        }
    }
}