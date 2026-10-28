#include "SSD.h"

const char* const SSD_NAME="SSD";
const int ENDURANCE=100;
const int TRIM_DIV=10;
const int LIFE_PCT=100;

SSD::SSD():Storage(SSD_NAME,0),enduranceWrites(ENDURANCE),trimCount(0){}

SSD::SSD(int capacityGb):Storage(SSD_NAME,capacityGb),enduranceWrites(ENDURANCE),trimCount(0){}

int SSD::trim(){
    int freed=usedGb/TRIM_DIV;
    usedGb-=freed;
    trimCount++;
    return freed;
}

int SSD::lifeLeft(){
    int worn=writeCount*LIFE_PCT/enduranceWrites;
    return worn>=LIFE_PCT?0:LIFE_PCT-worn;
}
