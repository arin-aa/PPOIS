#include "HDD.h"

const char* const HDD_NAME="HDD";
const int HDD_READ_SPEED_MB_PER_SEC=150;
const int MAX_BAD_SECTORS=100;

HDD::HDD():Storage(HDD_NAME,0,HDD_READ_SPEED_MB_PER_SEC),rpm(0),badSectors(0),fragmentationPercent(0){}

HDD::HDD(int capacityGb,int rpm):Storage(HDD_NAME,capacityGb,HDD_READ_SPEED_MB_PER_SEC),rpm(rpm),badSectors(0),fragmentationPercent(0){}

std::string HDD::describe(){
    return "HDD "+std::to_string(capacityGb)+"GB";
}

bool HDD::defragment(){
    if(badSectors>MAX_BAD_SECTORS){
        return false;
    }
    fragmentationPercent=0;
    return true;
}
