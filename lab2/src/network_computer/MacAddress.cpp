#include "MacAddress.h"

const int MAC_LENGTH=17;
const int MAC_GROUP_WIDTH=3;
const char MAC_SEPARATOR=':';

MacAddress::MacAddress():value(""),vendor(""){}

MacAddress::MacAddress(const std::string& value,const std::string& vendor):value(value),vendor(vendor){}

bool MacAddress::isValid(){
    if(static_cast<int>(value.size())!=MAC_LENGTH){
        return false;
    }
    for(int index=0; index<MAC_LENGTH; index++){
        bool isSeparatorSlot=(index+1)%MAC_GROUP_WIDTH==0;
        if(isSeparatorSlot && value[index]!=MAC_SEPARATOR){
            return false;
        }
    }
    return true;
}
