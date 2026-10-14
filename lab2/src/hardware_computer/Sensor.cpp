#include "Sensor.h"

Sensor::Sensor():unit(""),value(0.0),threshold(0.0){}

Sensor::Sensor(const std::string& unit,double threshold):unit(unit),value(0.0),threshold(threshold){}

bool Sensor::isCritical(){
    return value>=threshold;
}