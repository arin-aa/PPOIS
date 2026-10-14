#include "Storage.h"
#include "ComputerExceptions.h"

Storage::Storage():Component("","",5,100),capacityGb(0),usedGb(0),readSpeedMBs(0){}

Storage::Storage(const std::string& name,int capacityGb,int readSpeedMBs):Component(name,"Generic",5,100),capacityGb(capacityGb),usedGb(0),readSpeedMBs(readSpeedMBs){}

bool Storage::write(int gb){
    if(gb<=0){
        return false;
    }
    if(usedGb+gb>capacityGb){
        throw DiskFullException("disk is full");
    }
    usedGb+=gb;
    return true;
}

bool Storage::erase(int gb){
    if(gb<=0){
        return false;
    }
    if(gb>usedGb){
        return false;
    }
    usedGb-=gb;
    return true;
}

int Storage::freeSpace(){
    return capacityGb-usedGb;
}