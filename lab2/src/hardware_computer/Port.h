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
    explicit Port(const std::string& type);

    void plug(Cable* newCable);
    void unplug();
    bool connectPeripheral(Peripheral* peripheral);

    friend class Cable;
};
