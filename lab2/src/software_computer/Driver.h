#pragma once
#include "Software.h"
#include <string>

class Component;
class Storage;
class OperatingSystem;

class Driver:public Software{
private:
    std::string deviceName;
    bool isSigned;
    bool isLoaded;

public:
    Driver();
    Driver(const std::string& name,const std::string& deviceName,bool isSigned);

    bool install(Storage* storage) override;
    bool uninstall(Storage* storage) override;
    bool matches(Component* component);

    friend class OperatingSystem;
};