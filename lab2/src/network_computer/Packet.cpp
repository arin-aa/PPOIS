#include "Packet.h"
#include "IpAddress.h"

Packet::Packet():source(nullptr),destination(nullptr),sizeBytes(0),ttl(64){}

Packet::Packet(IpAddress* source,IpAddress* destination,int sizeBytes):source(source),destination(destination),sizeBytes(sizeBytes),ttl(64){}

bool Packet::isValid(){
    if(!source || !destination){
        return false;
    }
    if(sizeBytes<=0){
        return false;
    }
    return source->isValid() && destination->isValid();
}

int Packet::decrementTtl(){
    if(ttl<=0){
        return -1;
    }
    ttl--;
    return ttl;
}