#pragma once
#include <string>

class Application;
class OperatingSystem;

class Process{
private:
    int pid;
    int ramUsageMb;
    std::string state;
    Application* app;

public:
    Process();
    Process(int pid,Application* app,int ramUsageMb);

    void suspend();
    void resume();
    void terminate();
    std::string getState();
    int getPid();

    friend class OperatingSystem;
};
