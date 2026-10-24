#pragma once
#include <memory>
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
    explicit SystemBuilder(CompatibilityChecker* checker);

    bool installMotherboard(Motherboard* newMotherboard);
    bool installPsu(PSU* newPsu);
    bool installCase(Case* newChassis);
    bool addRam(RAM* ram);
    std::unique_ptr<Computer> build();
};
