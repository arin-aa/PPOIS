#pragma once
#include "Component.h"

class DiagnosticService;

class Storage:public Component{
protected:
    int capacityGb;
    int usedGb;
    int readSpeedMBs;

public:
    Storage();
    Storage(const std::string& name,int capacityGb,int readSpeedMBs);

    bool write(int gb);
    bool erase(int gb);
    int freeSpace();

    friend class DiagnosticService;
};