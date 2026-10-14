#pragma once
#include "Computer.h"

class Battery;
class Monitor;

class Laptop:public Computer{
private:
    Battery* battery;
    Monitor* display;
    double weightKg;

public:
    Laptop();
    Laptop(const std::string& hostname,double weightKg);

    void switchToBattery();
    void closeLid();
};