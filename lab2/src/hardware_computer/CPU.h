#pragma once
#include <string>
#include "Component.h"

class Sensor;
class CompatibilityChecker;
class Chipset;
class Motherboard;

class CPU:public Component{
private:
    int cores;
    double frequencyGHz;
    std::string socket;
    Sensor* tempSensor;

public:
    CPU();
    CPU(const std::string& socket,int cores,double ghz);

    std::string describe() override;
    void runLoad(int percent);
    bool isOverheated();
    void overclock(double ghz);

    friend class CompatibilityChecker;
    friend class Chipset;
    friend class Motherboard;
};