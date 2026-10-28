#include "IpAddress.h"
#include <cstdio>
#include "ComputerExceptions.h"

const int OCTETS=4;
const int MAX_OCTET=255;
const int BITS_IN_OCTET=8;

static bool parse(const std::string& text,int octets[OCTETS]){
    char tail;
    if(sscanf(text.c_str(),"%d.%d.%d.%d%c",&octets[0],&octets[1],&octets[2],&octets[3],&tail)!=OCTETS){
        return false;
    }
    for(int index=0;index<OCTETS;index++){
        if(octets[index]<0 || octets[index]>MAX_OCTET){
            return false;
        }
    }
    return true;
}

IpAddress::IpAddress():address(""),subnetMask(0){}

IpAddress::IpAddress(const std::string& address,int subnetMask):address(address),subnetMask(subnetMask){}

void IpAddress::validate(){
    int octets[OCTETS];
    if(!parse(address,octets)){
        throw InvalidAddressException("malformed IP address: "+address);
    }
}

bool IpAddress::sameSubnet(const std::string& other){
    int mine[OCTETS];
    int theirs[OCTETS];
    if(!parse(address,mine) || !parse(other,theirs)){
        throw InvalidAddressException("cannot compare "+address+" with "+other);
    }
    for(int index=0;index<subnetMask/BITS_IN_OCTET;index++){
        if(mine[index]!=theirs[index]){
            return false;
        }
    }
    return true;
}
