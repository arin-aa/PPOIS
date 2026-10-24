#pragma once
#include "Peripheral.h"

class Mouse:public Peripheral{
private:
    int dpi;
    int buttonsCount;

public:
    Mouse();
    Mouse(int dpi,int buttonsCount);

    bool setDpi(int newDpi);
    int getDpi();
};
