#pragma once
#include <vector>
#include "Computer.h"

class GPU;
class Cooler;

class Workstation:public Computer{
private:
    std::vector<GPU*> gpus;
    std::vector<Cooler*> coolers;

public:
    Workstation();
    explicit Workstation(const std::string& hostname);

    void installGpu(GPU* newGpu);
    int renderTask(int complexity);
};
