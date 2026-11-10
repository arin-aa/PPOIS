/**
 * @file Radiator.h
 * @brief Declaration of the Radiator class.
 */
#pragma once
#include "Cooler.h"

/**
 * @class Radiator
 * @brief Radiator class for liquid cooling.
 */
class Radiator:public Cooler{
private:
    int radiatorLengthMm;///<Radiator length in mm.
    int coolantMl;///<Coolant volume in ml.

public:
/**
 * @brief Default constructor.
 */
    Radiator();

/**
 * @brief Constructor with parameters.
 * @param radiatorLengthMm Length.
 * @param maxTdpWatts Maximum TDP.
 */
    Radiator(int radiatorLengthMm,int maxTdpWatts);

/**
 * @brief Tops up the coolant.
 * @param milliliters Volume to add.
 * @return Resulting volume, must not exceed capacity.
 */
    int refill(int milliliters);
};