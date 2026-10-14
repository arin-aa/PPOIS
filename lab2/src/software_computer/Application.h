#pragma once
#include "Software.h"
#include <string>

class Computer;
class Storage;

class Application:public Software{
private:
    int requiredRamMb;
    std::string licenseKey;

public:
    Application();
    Application(const std::string& name,const std::string& version,int sizeMb,int requiredRamMb,const std::string& licenseKey);

    bool install(Storage* storage) override;
    bool uninstall(Storage* storage) override;

    bool checkLicense(const std::string& key);
    bool canRunOn(Computer* computer);
};