#pragma once
#include <string>

class CPU;

class Chipset{
private:
    std::string model;
    int maxPcieLanes;

public:
    Chipset();
    Chipset(const std::string& model,int maxPcieLanes);

    bool supportsCpu(CPU* cpu);
};