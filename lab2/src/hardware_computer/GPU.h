#pragma once
#include "Component.h"

class Sensor;

class GPU:public Component{
private:
    int vramGb;
    int coreClockMhz;
    Sensor* tempSensor;

public:
    GPU();
    GPU(int vramGb,int coreClockMhz);

    std::string describe() override;
    void runLoad(int percent);
    bool isSufficientFor(int neededVram);
};