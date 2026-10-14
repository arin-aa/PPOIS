#include "Laptop.h"
#include "Battery.h"
#include "Monitor.h"

Laptop::Laptop():Computer(),battery(nullptr),display(nullptr),weightKg(2.0){}

Laptop::Laptop(const std::string& hostname,double weightKg):Computer(hostname),battery(nullptr),display(nullptr),weightKg(weightKg){}

void Laptop::switchToBattery(){
    if(!battery){
        return;
    }
    battery->discharge(1);
}

void Laptop::closeLid(){
    powerOff();
}