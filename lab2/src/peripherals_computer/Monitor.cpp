#include "Monitor.h"

const int MONITOR_MAX_PERCENT=100;
const char* const MONITOR_NAME="Monitor";
const int DEFAULT_BRIGHTNESS=50;

Monitor::Monitor():Peripheral(MONITOR_NAME),resolution(""),refreshRateHz(0),brightness(DEFAULT_BRIGHTNESS){}

Monitor::Monitor(const std::string& resolution,int refreshRateHz):Peripheral(MONITOR_NAME),resolution(resolution),refreshRateHz(refreshRateHz),
    brightness(DEFAULT_BRIGHTNESS){}

void Monitor::setBrightness(int value){
    if(value<0 || value>MONITOR_MAX_PERCENT){
        return;
    }
    brightness=value;
}

int Monitor::getBrightness(){
    return brightness;
}
