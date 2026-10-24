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
    double frequencyGhz;
    std::string socket;
    Sensor* tempSensor;

public:
    CPU();
    CPU(const std::string& socket,int cores,double frequencyGhz);

    std::string describe() override;
    void runLoad(int percent);
    bool isOverheated();
    void overclock(double newFrequencyGhz);
    double getFrequencyGhz();

    friend class CompatibilityChecker;
    friend class Chipset;
    friend class Motherboard;
};
