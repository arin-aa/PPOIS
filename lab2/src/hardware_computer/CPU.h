/**
 * @file CPU.h
 * @brief Declaration of the CPU class.
 */
#pragma once
#include <string>
#include "Component.h"

class Sensor;

/**
 * @class CPU
 * @brief Processor class.
 */
class CPU:public Component{
private:
    int cores;///<Number of cores.
    double frequencyGhz;///<Clock frequency in GHz.
    int loadPercent;///<Current load in percent.
    std::string socket;///<Processor socket.
    Sensor* tempSensor;///<Pointer to the temperature sensor.

public:
/**
* @brief Default constructor.
*/
    CPU();

/**
 * @brief Constructor with parameters.
 * @param socket Socket.
 * @param cores Number of cores.
 * @param frequencyGhz Frequency.
 * @param tempSensor Temperature sensor (default nullptr).
 */
    CPU(const std::string& socket,int cores,double frequencyGhz,Sensor* tempSensor=nullptr);

/**
 * @brief Applies load to the processor.
 * @param percent Load percentage.
 * @exception InvalidConfigurationException if the load is outside the range from 0 to 100.
 * @exception OverheatingException on critical temperature.
 */
    void runLoad(int percent);

/**
 * @brief Checks processor socket compatibility with the motherboard.
 * @param boardSocket Motherboard socket.
 * @exception IncompatibleSocketException on mismatch.
 */
    void checkSocket(const std::string& boardSocket);
};