#include "MacAddress.h"

MacAddress::MacAddress():value(""),vendor(""){}

MacAddress::MacAddress(const std::string& value,const std::string& vendor):value(value),vendor(vendor){}

bool MacAddress::isValid(){
    if(value.size()!=17){
        return false;
    }
    for(int i=0;i<17;i++){
        if((i+1)%3==0){
            if(value[i]!=':'){
                return false;
            }
        }
    }
    return true;
}