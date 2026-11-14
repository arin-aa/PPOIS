/**
 * @file Cable.h
 * @brief Declaration of the Cable class.
 */
#pragma once
#include <string>

/**
 * @class Cable
 * @brief Class representing a connection cable.
 */
class Cable{
private:
    std::string type;///<Cable type
    double lengthMeters;///<Cable length in meters.
    int maxMbps;///<Maximum throughput.

public:
/**
 * @brief Default constructor.
 */
    Cable();

/**
 * @brief Constructor with parameters.
 * @param type Cable type.
 * @param lengthMeters Length.
 * @param maxMbps Maximum speed.
 */
    Cable(const std::string& type,double lengthMeters,int maxMbps);

/**
 * @brief Checks cable compatibility with the port.
 * @param portType Port type.
 * @exception InvalidConfigurationException if the types do not match.
 */ 
    void match(const std::string& portType);

/**
 * @brief Calculates the actual throughput taking into account attenuation.
 * @return Effective speed in Mbps.
 */
    int effectiveMbps();
};