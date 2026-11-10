/**
 * @file PSU.h
 * @brief Declaration of the PSU class.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class PSU
 * @brief Power supply unit class.
 */
class PSU:public Component{
private:
    int wattage;///<Wattage.
    std::string certification;///<Certification.

public:
/**
 * @brief Default constructor.
 */
    PSU();

/**
 * @brief Constructor with parameters.
 * @param wattage Wattage.
 * @param certification Certification.
 */
    PSU(int wattage,const std::string& certification);

/**
 * @brief Calculates the power reserve.
 * @param loadWatts Current load.
 * @return Reserve.
 */
    int reserve(int loadWatts);

/**
 * @brief Calculates consumption from the mains.
 * @param loadWatts Useful load.
 * @return Consumption from the outlet.
 */
    int wallDraw(int loadWatts);
};