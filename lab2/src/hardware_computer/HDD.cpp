#include "HDD.h"

HDD::HDD():Storage("HDD",0,150),rpm(0),badSectors(0){}

HDD::HDD(int capacityGb,int rpm):Storage("HDD",capacityGb,150),rpm(rpm),badSectors(0){}

std::string HDD::describe(){
    return "HDD "+std::to_string(capacityGb)+"GB";
}

void HDD::defragment(){
    if(badSectors>100){
        return;
    }
}