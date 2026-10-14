#pragma once
#include <string>

class Cable;
class Peripheral;

class Port{
private:
    std::string type;
    Cable* cable;

public:
    Port();
    Port(const std::string& type);

    void plug(Cable* c);
    void unplug();
    bool connectPeripheral(Peripheral* p);

    friend class Cable;
};