/**
 * @file Cooler.h
 * @brief Declaration of the Cooler class.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class Cooler
 * @brief Class for cooling systems.
 */
class Cooler:public Component{
protected:
    int maxTdpWatts;///< Maximum heat dissipation capacity

public:
/**
 * @brief Default constructor.
 */ 
    Cooler();

/**
 * @brief Constructor with parameters.
 * @param name Cooler name.
 * @param maxTdpWatts Maximum TDP.
 */
    Cooler(const std::string& name,int maxTdpWatts);

/**
 * @brief Calculates cooling headroom.
 * @param tdp Current processor heat dissipation.
 * @return Difference between maximum and current TDP.
 */
    int headroom(int tdp);
};