#include "Monitor.h"

const char* const MONITOR_NAME="Monitor";
const int MAX_BRIGHT=100;
const int START_BRIGHT=50;
const double MILLION=1000000.0;

Monitor::Monitor():Peripheral(MONITOR_NAME),widthPx(0),heightPx(0),brightness(START_BRIGHT){}

Monitor::Monitor(int widthPx,int heightPx):Peripheral(MONITOR_NAME),widthPx(widthPx),heightPx(heightPx),brightness(START_BRIGHT){}

int Monitor::adjustBrightness(int delta){
    brightness+=delta;
    if(brightness<0){
        brightness=0;
    }
    if(brightness>MAX_BRIGHT){
        brightness=MAX_BRIGHT;
    }
    return brightness;
}

double Monitor::megapixels(){
    return widthPx*heightPx/MILLION;
}
