#pragma once
#include "Peripheral.h"
#include <string>

class Keyboard:public Peripheral{
private:
    std::string layout;
    bool isMechanical;

public:
    Keyboard();
    Keyboard(const std::string& layout,bool isMechanical);

    bool changeLayout(const std::string& newLayout);
};