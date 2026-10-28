#include "PSU.h"

const char* const PSU_NAME="PSU";
const char* const PSU_MAKER="Corsair";
const char* const GOLD="80+ Gold";
const int GOLD_EFF=90;
const int BASE_EFF=80;
const int PCT_ALL=100;

PSU::PSU():Component(PSU_NAME,PSU_MAKER,0),wattage(0),certification(""){}

PSU::PSU(int wattage,const std::string& certification):Component(PSU_NAME,PSU_MAKER,0),wattage(wattage),certification(certification){}

int PSU::reserve(int loadWatts){
    return wattage-loadWatts;
}

int PSU::wallDraw(int loadWatts){
    int efficiency=certification==GOLD?GOLD_EFF:BASE_EFF;
    return loadWatts*PCT_ALL/efficiency;
}
