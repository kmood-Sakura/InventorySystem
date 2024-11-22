#include "request/request.h"
#include "service/common_service/read/read_file_service.h"
#include "service/search_data_service/search_data_service.h"

int main(){
    userFilter request;
    GetRequestUserFilterData(&request); //still not allow for filter by name
    int itemCount;
    Goods* data = searchCSVfile("tempTest_pam.csv", &itemCount, &request);
    int times = 0;
    for(int i=1;i<=itemCount;i++){
        printf("%d : ",i);
        printGoods(data);
        data++;
    }
    return 0;
}