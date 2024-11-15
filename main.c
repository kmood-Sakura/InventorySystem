#include "handler/handler.h"
#include "request/request.h"
int main(){
    userFilter request;
    GetRequestUserFilterData(&request);
    userFilter temp;
    if(request.name[0] != '*'){ //string hardly to compare
        printf("request name : %s",request.name);
    }
    if(request.price != -1){
        printf("request price : %d",request.price);
    }
    return 0;
}