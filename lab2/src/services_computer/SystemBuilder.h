#pragma once
#include <vector>

class CompatibilityChecker;
class Motherboard;
class PSU;
class Case;
class RAM;
class Computer;

class SystemBuilder{
private:
    CompatibilityChecker* checker;
    Motherboard* motherboard;
    PSU* psu;
    Case* chassis;
    std::vector<RAM*> rams;

public:
    SystemBuilder();
    SystemBuilder(CompatibilityChecker* checker);

    bool installMotherboard(Motherboard* mb);
    bool addRam(RAM* ram);
    Computer* build();
};