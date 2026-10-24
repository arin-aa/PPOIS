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
    explicit Peripheral(const std::string& name);
    virtual ~Peripheral()=default;

    bool connectTo(Port* targetPort);
    void disconnect();

    friend class Port;
};
