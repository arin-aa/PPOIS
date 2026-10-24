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
class SystemBuilder;
class Application;

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
    explicit Computer(const std::string& hostname);
    virtual ~Computer()=default;

    void powerOn();
    void powerOff();
    void addStorage(Storage* storage);
    void installOs(OperatingSystem* newOs);
    int totalPowerDraw();
    bool isOn();
    std::string getHostname();

    friend class ReportGenerator;
    friend class DiagnosticService;
    friend class SystemBuilder;
    friend class Application;
};
