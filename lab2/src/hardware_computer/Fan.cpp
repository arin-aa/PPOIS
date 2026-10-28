#include "Fan.h"

const char* const FAN_NAME="Fan";
const char* const FAN_MAKER="Noctua";
const int FAN_WATTS=3;
const int MAX_RPM=2000;
const int FLOW_DIV=100;

Fan::Fan():Component(FAN_NAME,FAN_MAKER,FAN_WATTS),rpm(0),sizeMm(0){}

Fan::Fan(int sizeMm,int rpm):Component(FAN_NAME,FAN_MAKER,FAN_WATTS),rpm(rpm),sizeMm(sizeMm){}

int Fan::accelerate(int delta){
    rpm+=delta;
    if(rpm<0){
        rpm=0;
    }
    if(rpm>MAX_RPM){
        rpm=MAX_RPM;
    }
    return rpm;
}

int Fan::airflow(){
    return rpm*sizeMm/FLOW_DIV;
}
