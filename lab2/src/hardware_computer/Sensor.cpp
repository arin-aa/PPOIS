#include "Sensor.h"

Sensor::Sensor():value(0.0),threshold(0.0),readings(0){}

Sensor::Sensor(double threshold):value(0.0),threshold(threshold),readings(0){}

void Sensor::measure(double reading){
    value=(value*readings+reading)/(readings+1);
    readings++;
}

double Sensor::margin(){
    return threshold-value;
}
