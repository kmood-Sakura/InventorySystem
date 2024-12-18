#include <stdio.h>

#include "../log_service.h"

void COMMON_log(const char* id,const char *type, const char * path_Data, int quanitty){
    printf("--------------------------------------\n");
    printf("object id : %s was %s to %s\n",id,type,path_Data);
    printf("--------------------------------------\n");
}

void GOODS_log(GOODS *goods, const char *type, const char * path_Data, int quanitty){
    printf("--------------------------------------\n");
    for(int i=0;i<quanitty;i++){
        printf("ID : %s\n",goods->id);
        printf("Name : %s\n",goods->name);
        printf("Price : %.2lf\n",goods->price);
        printf("Quantity : %d\n",goods->quantity);
        printf("Description : %s\n",goods->description);
    }
    printf("----------was--%s--into--%s---------------\n",type,path_Data);
}

void USER_log(USER *user, const char *type, const char * path_Data,int quantity){
    printf("--------------------------------------\n");
    for(int i=0;i<quantity;i++){
        printf("ID : %s\n",user->id);
        printf("Name : %s\n",user->name);
        printf("Email : %s\n",user->email);
        printf("Phone : %s\n",user->phone);
        printf("Password : %s\n",user->password);
    }
    printf("----------was--%s--into--%s---------------\n",type,path_Data);
}

/*
void Coupon_log(Coupon *coupon, const char *type, const char * path_Data, int quantity){
    for(int i=0;i<quantity;i++){    
        printf("------------------Data-------------------\n");
        printf("ID : %s\n",coupon->couponCode);
        printf("Name : %.2lf\n",coupon->percentage);
        printf("Price : %d\n",coupon->amount);
        printf("----------was--%s--into--%s---------------\n",type,path_Data);
    }
}*/

void Order_log(Order *order, const char *type, const char * path_Data, int quantity){
    for(int i=0;i<quantity;i++){
        printf("------------------Data-------------------\n");
        printf("ID : %s\n",order->id);
        printf("Goods ID : %s\n",order->goodsid);
        printf("Buyer ID : %s\n",order->userid);
        printf("Price : %.2lf\n",order->price);
        printf("Quantity : %d\n",order->quantity);
        printf("----------was--%s--into--%s---------------\n",type,path_Data);
    }
}