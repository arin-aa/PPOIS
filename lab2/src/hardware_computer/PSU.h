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

    int totalDraw(const std::vector<Component*>& components);

public:
    PSU();
    PSU(int wattage,const std::string& certification);

    std::string describe() override;
    bool canPower(const std::vector<Component*>& components);
    int loadPercent(const std::vector<Component*>& components);
    bool connect(PowerConnector* connector);

    friend class CompatibilityChecker;
};
