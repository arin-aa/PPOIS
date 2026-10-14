#pragma once
#include <string>
#include <vector>

class Motherboard;
class PSU;
class Case;
class Storage;
class OperatingSystem;
class User;
class ReportGenerator;
class DiagnosticService;

class Computer{
protected:
    std::string hostname;
    bool isPoweredOn;
    Motherboard* motherboard;
    PSU* psu;
    Case* chassis;
    std::vector<Storage*> storages;
    OperatingSystem* os;
    User* owner;

public:
    Computer();
    Computer(const std::string& hostname);
    virtual ~Computer()=default;

    void powerOn();
    void powerOff();
    void addStorage(Storage* storage);
    void installOs(OperatingSystem* newOs);
    int totalPowerDraw();

    friend class ReportGenerator;
    friend class DiagnosticService;
    friend class Application;
};