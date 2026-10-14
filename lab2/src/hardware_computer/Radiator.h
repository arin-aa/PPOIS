#pragma once
#include "Cooler.h"

class Radiator:public Cooler{
private:
    int lengthMm;
    int coolantLevel;

public:
    Radiator();
    Radiator(int lengthMm);

    std::string describe() override;
    bool refillCoolant(int ml);
};