#include "Cable.h"
#include "Port.h"

Cable::Cable():type(""),lengthM(0.0){}

Cable::Cable(const std::string& type,double lengthM):type(type),lengthM(lengthM){}

bool Cable::isCompatibleWith(Port* port){
    if(!port){
        return false;
    }
    return type==port->type;
}