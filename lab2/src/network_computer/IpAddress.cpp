#include "IpAddress.h"
#include <algorithm>

const int DEFAULT_SUBNET_MASK=24;
const int MIN_SUBNET_MASK=0;
const int MAX_SUBNET_MASK=32;
const int IP_SEPARATOR_COUNT=3;
const char IP_SEPARATOR='.';

IpAddress::IpAddress():address(""),subnetMask(DEFAULT_SUBNET_MASK){}

IpAddress::IpAddress(const std::string& address,int subnetMask):address(address),subnetMask(subnetMask){}

bool IpAddress::isValid(){
    int separators=static_cast<int>(std::count(address.begin(),address.end(),IP_SEPARATOR));
    if(separators!=IP_SEPARATOR_COUNT){
        return false;
    }
    return subnetMask>=MIN_SUBNET_MASK && subnetMask<=MAX_SUBNET_MASK;
}

bool IpAddress::isInSameSubnet(IpAddress* other){
    if(!other){
        return false;
    }
    std::size_t lastDotHere=address.find_last_of(IP_SEPARATOR);
    std::size_t lastDotThere=other->address.find_last_of(IP_SEPARATOR);
    if(lastDotHere==std::string::npos || lastDotThere==std::string::npos){
        return false;
    }
    return address.substr(0,lastDotHere)==other->address.substr(0,lastDotThere);
}
