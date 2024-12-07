#include <stdio.h>
#include <stdlib.h>

#include "../owner_page.h"

void Owner_Page(void){
    while(1){
        char key;
        printf("system command : ");
        scanf(" %c",&key);
        switch (key){
            case 'O':
                break;
            case 'S':
                break;
            case '+':
                break;
            case '-':
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