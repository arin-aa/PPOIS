#include "RAM.h"
#include "ComputerExceptions.h"

const char* const RAM_NAME="RAM";
const char* const RAM_MANUFACTURER="Kingston";
const int RAM_POWER_WATTS=5;
const int RAM_LENGTH_MM=133;

RAM::RAM():Component(RAM_NAME,RAM_MANUFACTURER,RAM_POWER_WATTS,RAM_LENGTH_MM),capacityGb(0),type(""),speedMhz(0),usedGb(0){}

RAM::RAM(int capacityGb,const std::string& type,int speedMhz):Component(RAM_NAME,RAM_MANUFACTURER,RAM_POWER_WATTS,RAM_LENGTH_MM),
    capacityGb(capacityGb),type(type),speedMhz(speedMhz),usedGb(0){}

std::string RAM::describe(){
    return "RAM "+type+" "+std::to_string(capacityGb)+"GB";
}

bool RAM::allocate(int gb){
    if(gb<=0){
        return false;
    }
    if(usedGb+gb>capacityGb){
        throw MemoryOverflowException("not enough RAM");
    }
    usedGb+=gb;
    return true;
}

bool RAM::release(int gb){
    if(gb<=0 || gb>usedGb){
        return false;
    }
    usedGb-=gb;
    return true;
}

int RAM::getUsedGb(){
    return usedGb;
}
