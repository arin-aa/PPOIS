#include "RAM.h"
#include "ComputerExceptions.h"

RAM::RAM():Component("RAM","Kingston",5,133),capacityGb(0),type(""),speedMhz(0),usedGb(0){}

RAM::RAM(int capacityGb,const std::string& type,int speedMhz):Component("RAM","Kingston",5,133),capacityGb(capacityGb),type(type),speedMhz(speedMhz),usedGb(0){}

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
    if(gb<=0){
        return false;
    }
    if(gb>usedGb){
        return false;
    }
    usedGb-=gb;
    return true;
}