#pragma once
#include <string>
#include <vector>
#include "Software.h"

class Driver;
class Application;
class Process;
class Folder;
class Storage;

class OperatingSystem:public Software{
private:
    std::string family;
    std::string architecture;
    std::vector<Driver*> drivers;
    std::vector<Process*> processes;
    Folder* rootFolder;
    bool isBooted;

public:
    OperatingSystem();
    OperatingSystem(const std::string& family,const std::string& architecture,const std::string& version);

    bool install(Storage* storage) override;
    bool uninstall(Storage* storage) override;

    bool boot();
    Process* startProcess(Application* app);
    bool killProcess(int pid);
    bool installDriver(Driver* driver);
};