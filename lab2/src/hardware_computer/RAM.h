#pragma once
#include <string>
#include "Component.h"

class CompatibilityChecker;

class RAM:public Component{
private:
    int capacityGb;
    std::string type;
    int speedMhz;
    int usedGb;

public:
    RAM();
    RAM(int capacityGb,const std::string& type,int speedMhz);

    std::string describe() override;
    bool allocate(int gb);
    bool release(int gb);

    friend class CompatibilityChecker;
};