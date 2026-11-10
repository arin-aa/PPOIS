/**
 * @file Storage.h
 * @brief Declaration of the Storage class.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class Storage
 * @brief Class for all storage devices.
 */
class Storage:public Component{
protected:
    int capacityGb;///<Capacity in GB.
    int usedGb;///<How many GB are occupied.
    int writeCount;///<Number of write operations.

public:
/**
 * @brief Default constructor.
 */
    Storage();

/**
 * @brief Constructor with parameters.
 * @param name Storage device name.
 * @param capacityGb Capacity.
 */
    Storage(const std::string& name,int capacityGb);

/**
 * @brief Writes data.
 * @param gb Volume.
 * @exception DiskFullException if there is not enough space.
 */
    void write(int gb);

/**
 * @brief Erases data.
 * @param gb Volume to erase.
 * @return Actually erased volume.
 */
    int erase(int gb);

/**
 * @brief Returns the amount of free space.
 * @return Free GB.
 */
    int freeSpace();

/**
* @brief Virtual method for calculating the remaining life.
* @return Percentage.
*/
    virtual int lifeLeft();
};