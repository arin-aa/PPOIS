#include "Cable.h"
#include "Port.h"

Cable::Cable():type(""),lengthMeters(0.0){}

Cable::Cable(const std::string& type,double lengthMeters):type(type),lengthMeters(lengthMeters){}

bool Cable::isCompatibleWith(Port* port){
    if(!port){
        return false;
    }
    return type==port->type;
}
