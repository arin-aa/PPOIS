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
    int maxGpuLength;
    std::vector<Fan*> fans;

public:
    Case();
    Case(const std::string& formFactor,int maxGpuLength);

    std::string describe() override;
    bool fits(Motherboard* mb);
    bool addFan(Fan* fan);

    friend class CompatibilityChecker;
};