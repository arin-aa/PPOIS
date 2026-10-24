#include "PSU.h"
#include "PowerConnector.h"

const int PSU_MAX_PERCENT=100;
const int PSU_NOT_AVAILABLE=-1;
const char* const PSU_NAME="PSU";
const char* const PSU_MANUFACTURER="Corsair";
const int PSU_POWER_WATTS=0;
const int PSU_LENGTH_MM=150;

PSU::PSU():Component(PSU_NAME,PSU_MANUFACTURER,PSU_POWER_WATTS,PSU_LENGTH_MM),wattage(0),certification(""){}

PSU::PSU(int wattage,const std::string& certification):Component(PSU_NAME,PSU_MANUFACTURER,PSU_POWER_WATTS,PSU_LENGTH_MM),wattage(wattage),
    certification(certification){}

std::string PSU::describe(){
    return "PSU "+std::to_string(wattage)+"W";
}

int PSU::totalDraw(const std::vector<Component*>& components){
    int totalWatts=0;
    for(Component* component:components){
        if(component){
            totalWatts+=component->powerWatts;
        }
    }
    return totalWatts;
}

bool PSU::canPower(const std::vector<Component*>& components){
    return totalDraw(components)<=wattage;
}

int PSU::loadPercent(const std::vector<Component*>& components){
    if(wattage==0){
        return PSU_NOT_AVAILABLE;
    }
    return totalDraw(components)*PSU_MAX_PERCENT/wattage;
}

bool PSU::connect(PowerConnector* connector){
    if(!connector || !connector->connect()){
        return false;
    }
    connectors.push_back(connector);
    return true;
}
