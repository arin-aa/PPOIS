#include "PSU.h"
#include "PowerConnector.h"
#include "Component.h"

PSU::PSU():Component("PSU","Corsair",0,150),wattage(0),certification(""){}

PSU::PSU(int wattage,const std::string& certification):Component("PSU","Corsair",0,150),wattage(wattage),certification(certification){}

std::string PSU::describe(){
    return "PSU "+std::to_string(wattage)+"W";
}

bool PSU::canPower(std::vector<Component*> components){
    int total=0;
    for(Component* c:components){
        if(c){
            total+=c->powerWatts;
        }
    }
    return total<=wattage;
}

int PSU::loadPercent(std::vector<Component*> components){
    if(wattage==0){
        return -1;
    }
    int total=0;
    for(Component* c:components){
        if(c){
            total+=c->powerWatts;
        }
    }
    return total*100/wattage;
}

bool PSU::connect(PowerConnector* c){
    if(!c){
        return false;
    }
    connectors.push_back(c);
    return true;
}