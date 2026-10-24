#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Software.h"

class Driver;
class Application;
class Process;
class Folder;
class Storage;
class Component;

class OperatingSystem:public Software{
private:
    std::string family;
    std::string architecture;
    std::vector<Driver*> drivers;
    std::vector<std::unique_ptr<Process>> processes;
    Folder* rootFolder;
    bool isBooted;
    int nextPid;

public:
    OperatingSystem();
    OperatingSystem(const std::string& family,const std::string& architecture,const std::string& version);
    ~OperatingSystem() override;

    bool install(Storage* storage) override;
    bool uninstall(Storage* storage) override;

    bool boot();
    Process* startProcess(Application* app);
    bool killProcess(int pid);
    bool installDriver(Driver* driver);
    Driver* findDriverFor(Component* component);
    bool isRunning();
    int getProcessCount();
};
