#pragma once
#include <string>

class CompatibilityChecker;
class Computer;
class PSU;
class Inventory;
class Driver;

class Component{
protected:
    std::string name;
    std::string manufacturer;
    int powerWatts;
    int lengthMM;

public:
    Component();
    Component(const std::string& name,const std::string& manufacturer,int powerWatts,int lengthMM);
    virtual ~Component()=default;

    virtual std::string describe()=0;

    friend class CompatibilityChecker;
    friend class Computer;
    friend class PSU;
    friend class Inventory;
    friend class Driver;
};