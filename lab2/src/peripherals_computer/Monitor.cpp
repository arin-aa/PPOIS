#include "Monitor.h"

Monitor::Monitor():Peripheral("Monitor"),resolution(""),refreshRateHz(0),brightness(50){}

Monitor::Monitor(const std::string& resolution,int refreshRateHz):Peripheral("Monitor"),resolution(resolution),refreshRateHz(refreshRateHz),brightness(50){}

void Monitor::setBrightness(int value){
    if(value<0 || value>100){
        return;
    }
    brightness=value;
}