#pragma once
#include "Computer.h"
#include <vector>

class GPU;
class Cooler;

class Workstation:public Computer{
private:
    std::vector<GPU*> gpu;
    std::vector<Cooler*> coolers;

public:
    Workstation();
    Workstation(const std::string& hostname);

    void installGpu(GPU* newGpu);
    int renderTask(int complexity);
};