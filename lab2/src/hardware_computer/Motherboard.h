#pragma once
#include <string>
#include <vector>
#include "Component.h"

class CPU;
class RAM;
class Chipset;
class Port;
class CompatibilityChecker;
class SystemBuilder;
class Case;
class Application;

class Motherboard:public Component{
private:
    std::string socket;
    int ramSlots;
    std::string formFactor;
    Chipset* chipset;
    CPU* cpu;
    std::vector<RAM*> ramModules;
    std::vector<Port*> ports;

public:
    Motherboard();
    Motherboard(const std::string& socket,int ramSlots,const std::string& formFactor);

    std::string describe() override;
    bool installCpu(CPU* newCpu);
    bool installRam(RAM* ram);
    bool hasFreeRamSlot();

    friend class CompatibilityChecker;
    friend class SystemBuilder;
    friend class Case;
    friend class Application;
};
