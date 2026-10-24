#include "Battery.h"

const int BATTERY_MAX_PERCENT=100;
const int DEGRADED_CYCLES=500;

Battery::Battery():capacityWh(0),chargePercent(0),cycles(0){}

Battery::Battery(int capacityWh):capacityWh(capacityWh),chargePercent(BATTERY_MAX_PERCENT),cycles(0){}

void Battery::charge(int percent){
    if(percent<=0){
        return;
    }
    chargePercent+=percent;
    if(chargePercent>BATTERY_MAX_PERCENT){
        chargePercent=BATTERY_MAX_PERCENT;
    }
}

void Battery::discharge(int percent){
    if(percent<=0){
        return;
    }
    chargePercent-=percent;
    if(chargePercent<0){
        chargePercent=0;
    }
    cycles++;
}

bool Battery::isDegraded(){
    return cycles>=DEGRADED_CYCLES;
}

int Battery::getChargePercent(){
    return chargePercent;
}

int Battery::getCycles(){
    return cycles;
}
