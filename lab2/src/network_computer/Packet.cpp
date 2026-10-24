#include "Packet.h"
#include "IpAddress.h"

const int PACKET_NOT_AVAILABLE=-1;
const int DEFAULT_TTL=64;

Packet::Packet():source(nullptr),destination(nullptr),sizeBytes(0),ttl(DEFAULT_TTL){}

Packet::Packet(IpAddress* source,IpAddress* destination,int sizeBytes):source(source),destination(destination),sizeBytes(sizeBytes),ttl(DEFAULT_TTL){}

bool Packet::isValid(){
    if(!source || !destination || sizeBytes<=0){
        return false;
    }
    return source->isValid() && destination->isValid();
}

int Packet::decrementTtl(){
    if(ttl<=0){
        return PACKET_NOT_AVAILABLE;
    }
    ttl--;
    return ttl;
}

int Packet::getTtl(){
    return ttl;
}
