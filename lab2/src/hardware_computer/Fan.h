#pragma once
#include "Component.h"

class Fan:public Component{
private:
    int rpm;
    int sizeMm;

public:
    Fan();
    explicit Fan(int sizeMm);

    std::string describe() override;
    void setSpeed(int newRpm);
    int getRpm();
};
