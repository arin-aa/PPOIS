#pragma once
#include "Cooler.h"

class Radiator:public Cooler{
private:
    int radiatorLengthMm;
    int coolantLevel;

public:
    Radiator();
    explicit Radiator(int radiatorLengthMm);

    std::string describe() override;
    bool refillCoolant(int milliliters);
    int getCoolantLevel();
};
