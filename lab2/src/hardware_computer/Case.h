#pragma once
#include <string>
#include <vector>
#include "Component.h"

class Motherboard;
class Fan;
class CompatibilityChecker;

class Case:public Component{
private:
    std::string formFactor;
    int maxGpuLengthMm;
    std::vector<Fan*> fans;

public:
    Case();
    Case(const std::string& formFactor,int maxGpuLengthMm);

    std::string describe() override;
    bool fits(Motherboard* board);
    bool addFan(Fan* fan);
    int getFanCount();

    friend class CompatibilityChecker;
};
