#pragma once

class Logger;
class Computer;
class Storage;
class Sensor;

class DiagnosticService{
private:
    Logger* logger;
    int issuesFound;

public:
    DiagnosticService();
    explicit DiagnosticService(Logger* logger);

    bool checkTemperature(Computer* computer,Sensor* sensor);
    bool checkStorage(Computer* computer,Storage* storage);
    int runFullDiagnostic(Computer* computer);
};
