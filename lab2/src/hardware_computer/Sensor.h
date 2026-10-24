#pragma once
#include <string>

class DiagnosticService;

class Sensor{
private:
    std::string unit;
    double value;
    double threshold;

public:
    Sensor();
    Sensor(const std::string& unit,double threshold);

    bool isCritical();

    friend class DiagnosticService;
};
