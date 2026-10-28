#include "MacAddress.h"
#include "ComputerExceptions.h"

const int MAC_LENGTH=17;
const int GROUP_LENGTH=3;
const char SEPARATOR=':';

MacAddress::MacAddress():value(""),vendor(""){}

MacAddress::MacAddress(const std::string& value,const std::string& vendor):value(value),vendor(vendor){}

void MacAddress::verify(){
    if(static_cast<int>(value.size())!=MAC_LENGTH){
        throw InvalidAddressException(vendor+" MAC address must be 17 characters: "+value);
    }
    for(int index=GROUP_LENGTH-1;index<MAC_LENGTH;index+=GROUP_LENGTH){
        if(value[index]!=SEPARATOR){
            throw InvalidAddressException("MAC address needs ':' separators: "+value);
        }
    }
}
