#include "Laptop.h"
#include "Battery.h"

const int PCT_PER_MIN=2;
const int WATTS_PER_INCH=2;

Laptop::Laptop():Computer(),screenInches(0),chargedMinutes(0),battery(nullptr){}

Laptop::Laptop(const std::string& hostname,int screenInches,Battery* battery):Computer(hostname),screenInches(screenInches),
    chargedMinutes(0),battery(battery){}

int Laptop::plugIn(int minutes){
    chargedMinutes+=minutes;
    return battery->charge(minutes*PCT_PER_MIN);
}

int Laptop::batteryMinutes(){
    return battery->runtimeMinutes(powerDraw());
}

int Laptop::powerDraw(){
    return Computer::powerDraw()+screenInches*WATTS_PER_INCH;
}
