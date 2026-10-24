#pragma once
#include "Peripheral.h"
#include <string>

class Monitor:public Peripheral{
private:
    std::string resolution;
    int refreshRateHz;
    int brightness;

public:
    Monitor();
    Monitor(const std::string& resolution,int refreshRateHz);

    void setBrightness(int value);
    int getBrightness();
};
