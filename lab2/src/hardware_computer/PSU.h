#pragma once
#include <string>
#include <vector>
#include "Component.h"

class PowerConnector;
class CompatibilityChecker;

class PSU:public Component{
private:
    int wattage;
    std::string certification;
    std::vector<PowerConnector*> connectors;

public:
    PSU();
    PSU(int wattage,const std::string& certification);

    std::string describe() override;
    bool canPower(std::vector<Component*> components);
    int loadPercent(std::vector<Component*> components);
    bool connect(PowerConnector* c);

    friend class CompatibilityChecker;
};