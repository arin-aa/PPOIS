/**
 * @file Port.h
 * @brief Declaration of the Port class.
 */

#pragma once
#include <string>

class Cable;

/**
 * @class Port
 * @brief Input/output port class.
 */
class Port{
private:
    std::string type;///<Port type.
    int speedMbps;///<Port throughput.
    Cable* cable;///<Connected cable.

public:
/**
 * @brief Default constructor.
 */
    Port();

/**
 * @brief Constructor with parameters.
 * @param type Port type.
 * @param speedMbps Speed.
 */
    Port(const std::string& type,int speedMbps);

/**
 * @brief Connects a cable to the port.
 * @param newCable Pointer to the cable.
 */
    void plug(Cable* newCable);

/**
 * @brief Calculates the actual throughput.
 * @return Speed in Mbps.
 * @exception PeripheralNotRespondingException if there is no cable.
 */
    int throughput();
};