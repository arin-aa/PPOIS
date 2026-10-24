#pragma once
#include "Component.h"

class DiagnosticService;

class Storage:public Component{
protected:
    int capacityGb;
    int usedGb;
    int readSpeedMbPerSec;

public:
    Storage();
    Storage(const std::string& name,int capacityGb,int readSpeedMbPerSec);

    bool write(int gb);
    bool erase(int gb);
    int freeSpace();
    int getUsedGb();

    friend class DiagnosticService;
};
