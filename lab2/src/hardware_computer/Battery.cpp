#include "Battery.h"

Battery::Battery():capacityWh(0),chargePercent(0),cycles(0){}

Battery::Battery(int capacityWh):capacityWh(capacityWh),chargePercent(100),cycles(0){}

void Battery::charge(int percent){
    if(percent<=0){
        return;
    }
    chargePercent+=percent;
    if(chargePercent>100){
        chargePercent=100;
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
    return cycles>=500;
}