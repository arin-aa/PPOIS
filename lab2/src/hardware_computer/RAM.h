/**
 * @file RAM.h
 * @brief Declaration of the RAM class.
 */
#pragma once
#include "Component.h"

/**
 * @class RAM
 * @brief Random access memory class.
 */
class RAM:public Component{
private:
    int capacityGb;///<Capacity in GB.
    int usedGb;///<How many GB are used.
    int speedMhz;///<Clock speed.

public:
/**
 * @brief Default constructor.
 */
    RAM();

/**
 * @brief Constructor with parameters.
 * @param capacityGb Capacity.
 * @param speedMhz Clock speed.
 */ 
    RAM(int capacityGb,int speedMhz);

/**
 * @brief Allocates memory for a process.
 * @param gb Requested amount.
 * @return Allocation time in ms.
 * @exception MemoryOverflowException if there is not enough memory.
 */    
    int allocate(int gb);

/**
 * @brief Returns the free amount.
 * @return Free GB.
 */
    int freeGb();
};