#include "SSD.h"

const char* const SSD_NAME="SSD";
const int SSD_READ_SPEED_MB_PER_SEC=500;
const int MAX_WEAR_PERCENT=100;

SSD::SSD():Storage(SSD_NAME,0,SSD_READ_SPEED_MB_PER_SEC),wearPercent(0){}

SSD::SSD(int capacityGb):Storage(SSD_NAME,capacityGb,SSD_READ_SPEED_MB_PER_SEC),wearPercent(0){}

std::string SSD::describe(){
    return "SSD "+std::to_string(capacityGb)+"GB";
}

void SSD::trim(){
    if(wearPercent>=MAX_WEAR_PERCENT){
        return;
    }
    usedGb=0;
}
