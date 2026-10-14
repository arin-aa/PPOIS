#include "IpAddress.h"

IpAddress::IpAddress():address(""),subnetMask(24){}

IpAddress::IpAddress(const std::string& address,int subnetMask):address(address),subnetMask(subnetMask){}

bool IpAddress::isValid(){
    int dots=0;
    for(char c:address){
        if(c=='.'){
            dots++;
        }
    }
    if(dots!=3 || address.empty()){
        return false;
    }
    if(subnetMask<0 || subnetMask>32){
        return false;
    }
    return true;
}

bool IpAddress::isInSameSubnet(IpAddress* other){
    if(!other){
        return false;
    }
    int pos=address.find_last_of('.');
    int pos2=other->address.find_last_of('.');
    if(pos<0 || pos2<0){
        return false;
    }
    return address.substr(0,pos)==other->address.substr(0,pos2);
}