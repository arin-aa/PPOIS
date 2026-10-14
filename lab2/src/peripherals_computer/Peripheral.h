#pragma once
#include <string>

class Port;

class Peripheral{
protected:
    std::string name;
    bool isConnected;
    Port* port;

public:
    Peripheral();
    Peripheral(const std::string& name);
    virtual ~Peripheral()=default;

    bool connectTo(Port* p);
    void disconnect();

    friend class Port;
};