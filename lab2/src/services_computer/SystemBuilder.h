/**
 * @file SystemBuilder.h
 * @brief Declaration of the SystemBuilder class.
 */
#pragma once

class CompatibilityChecker;

/**
 * @class SystemBuilder
 * @brief Configurator class for building a computer.
 * 
 * Tracks the budget, total power consumption of parts, 
 * and calculates the recommended power supply capacity.
 */
class SystemBuilder{
private:
    int budget;///<Total build budget.
    int spent;///<Amount spent.
    int partsWatts;///<Total power consumption of parts.
    CompatibilityChecker* checker;///<Pointer to the compatibility checker object.

public:
/**
 * @brief Default constructor.
 */
    SystemBuilder();

/**
 * @brief Constructor with parameters.
 * @param budget Budget.
 * @param checker Pointer to the checking module.
 */
    SystemBuilder(int budget,CompatibilityChecker* checker);

/**
 * @brief Adds a part to the build.
 * @param watts Power consumption of the part.
 * @param price Cost of the part.
 * @exception InvalidConfigurationException if the cost exceeds the budget.
 */
    void addPart(int watts,int price);

/**
 * @brief Calculates the power supply capacity margin.
 * @param psuWatts Wattage of the proposed PSU.
 * @return Power margin in watts.
 * @exception InsufficientPowerException if the margin is insufficient.
 */
    int powerMargin(int psuWatts);

/**
 * @brief Recommends the required power supply capacity.
 * @return Recommended wattage, rounded up to a step of 50.
 */
    int recommendedPsu();
};