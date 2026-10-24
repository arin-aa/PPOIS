#include "Storage.h"
#include "ComputerExceptions.h"

const char* const STORAGE_MANUFACTURER="Generic";
const int STORAGE_POWER_WATTS=5;
const int STORAGE_LENGTH_MM=100;

Storage::Storage():Component("","",STORAGE_POWER_WATTS,STORAGE_LENGTH_MM),capacityGb(0),usedGb(0),readSpeedMbPerSec(0){}

Storage::Storage(const std::string& name,int capacityGb,int readSpeedMbPerSec):
    Component(name,STORAGE_MANUFACTURER,STORAGE_POWER_WATTS,STORAGE_LENGTH_MM),capacityGb(capacityGb),usedGb(0),readSpeedMbPerSec(readSpeedMbPerSec){}

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
    if(gb<=0 || gb>usedGb){
        return false;
    }
    usedGb-=gb;
    return true;
}

int Storage::freeSpace(){
    return capacityGb-usedGb;
}

int Storage::getUsedGb(){
    return usedGb;
}
