#include "Battery.h"

const int FULL=100;
const int MIN_PER_HOUR=60;

Battery::Battery():capacityWh(0),chargePercent(0),cycles(0){}

Battery::Battery(int capacityWh,int chargePercent):capacityWh(capacityWh),chargePercent(chargePercent),cycles(0){}

int Battery::charge(int percent){
    chargePercent+=percent;
    if(chargePercent>=FULL){
        chargePercent=FULL;
        cycles++;
    }
    return chargePercent;
}

int Battery::runtimeMinutes(int watts){
    if(watts<=0){
        return 0;
    }
    int energyWh=capacityWh*chargePercent/FULL;
    return energyWh*MIN_PER_HOUR/watts;
}
