#include "Laptop.h"
#include "Battery.h"
#include "Monitor.h"

const double DEFAULT_LAPTOP_WEIGHT_KG=2.0;
const int DISCHARGE_ON_SWITCH_PERCENT=1;

Laptop::Laptop():Computer(),battery(nullptr),display(nullptr),weightKg(DEFAULT_LAPTOP_WEIGHT_KG){}

Laptop::Laptop(const std::string& hostname,double weightKg):Computer(hostname),battery(nullptr),display(nullptr),weightKg(weightKg){}

void Laptop::switchToBattery(){
    if(!battery){
        return;
    }
    battery->discharge(DISCHARGE_ON_SWITCH_PERCENT);
}

void Laptop::closeLid(){
    powerOff();
}
