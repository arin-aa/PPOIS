/**
 * @file SSD.h
 * @brief Declaration of the SSD class.
 */
#pragma once
#include "Storage.h"

/**
 * @class SSD
 * @brief Storage device class.
 */
class SSD:public Storage{
private:
    int enduranceWrites;///<Write endurance (cycles).
    int trimCount;///<Number of TRIM operations.

public:
/**
 * @brief Default constructor.
 */
    SSD();

/**
 * @brief Constructor with capacity specified.
 * @param capacityGb Capacity.
 */
    explicit SSD(int capacityGb);

/**
 * @brief Executes the TRIM command.
 * @return Freed space in GB.
 */ 
    int trim();

/**
* @brief Calculates the remaining resource.
* @return Percentage of remaining life.
*/ 
    int lifeLeft() override;
};