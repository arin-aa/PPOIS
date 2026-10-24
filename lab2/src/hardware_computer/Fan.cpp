#include "Fan.h"

const char* const FAN_NAME="Fan";
const char* const FAN_MANUFACTURER="Noctua";
const int FAN_POWER_WATTS=2;
const int FAN_LENGTH_MM=25;

Fan::Fan():Component(FAN_NAME,FAN_MANUFACTURER,FAN_POWER_WATTS,FAN_LENGTH_MM),rpm(0),sizeMm(0){}

Fan::Fan(int sizeMm):Component(FAN_NAME,FAN_MANUFACTURER,FAN_POWER_WATTS,FAN_LENGTH_MM),rpm(0),sizeMm(sizeMm){}

std::string Fan::describe(){
    return "Fan "+std::to_string(sizeMm)+"mm";
}

void Fan::setSpeed(int newRpm){
    if(newRpm<0){
        return;
    }
    rpm=newRpm;
}

int Fan::getRpm(){
    return rpm;
}
