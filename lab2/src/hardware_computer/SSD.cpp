#include "SSD.h"

SSD::SSD():Storage("SSD",0,500),wearPercent(0){}

SSD::SSD(int capacityGb):Storage("SSD",capacityGb,500),wearPercent(0){}

std::string SSD::describe(){
    return "SSD "+std::to_string(capacityGb)+"GB";
}

void SSD::trim(){
    if(wearPercent>=100){
        return;
    }
    usedGb=0;
}