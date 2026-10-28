#include "Storage.h"
#include "ComputerExceptions.h"

const char* const STORAGE_MAKER="Generic";
const int STORAGE_WATTS=5;
const int FULL_LIFE=100;

Storage::Storage():Component("",STORAGE_MAKER,STORAGE_WATTS),capacityGb(0),usedGb(0),writeCount(0){}

Storage::Storage(const std::string& name,int capacityGb):Component(name,STORAGE_MAKER,STORAGE_WATTS),capacityGb(capacityGb),usedGb(0),
    writeCount(0){}

void Storage::write(int gb){
    if(gb>freeSpace()){
        throw DiskFullException(name+" is full");
    }
    usedGb+=gb;
    writeCount++;
}

int Storage::erase(int gb){
    int removed=gb>usedGb?usedGb:gb;
    usedGb-=removed;
    return removed;
}

int Storage::freeSpace(){
    return capacityGb-usedGb;
}

int Storage::lifeLeft(){
    return FULL_LIFE;
}
