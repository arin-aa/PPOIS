#pragma once

class Motherboard;
class CPU;
class RAM;
class PSU;
class Case;
class Component;

class CompatibilityChecker{
private:
    bool strictMode;
    int checksDone;

public:
    CompatibilityChecker();
    explicit CompatibilityChecker(bool strictMode);

    bool checkSocket(Motherboard* board,CPU* cpu);
    int checkRam(Motherboard* board,RAM* ram);
    int checkPower(PSU* psu,Component* component);
    bool checkCaseFit(Case* chassis,Component* component);
};
