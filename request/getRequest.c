#include "request.h"

void GetRequestUserFilterData(userFilter *req) {
    char condition;

    printf("Filter by name? (y,n) : ");
    scanf(" %c", &condition); 
    if (condition == 'y') {
        printf("(within 50 characters) name : ");
        scanf("%50s", req->name);
    }else{
        strcpy(req->name,"*");
    }
    printf("Filter by price? (y,n) : ");
    scanf(" %c", &condition); 
    if (condition == 'y') {
        printf("The price : ");
        scanf("%lf", &req->price);
        printf("Lower or higher or equal to (<,>,=) : ");
        scanf(" %c", &req->condition_price); 

        printf("get request price : %f, comd : %c\n",req->price,req->condition_price);
    }else{
        req->condition_price = ' ';
        req->price = -1;
    }
}