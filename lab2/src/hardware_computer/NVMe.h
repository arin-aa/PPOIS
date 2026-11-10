/**
 * @file NVMe.h
 * @brief Declaration of the NVMe class.
 */
#pragma once
#include "Storage.h"

/**
 * @class NVMe
 * @brief Class of the storage device standard.
 */
class NVMe:public Storage{
private:
    int pcieLanes;///<Number of PCIe lanes.
    int queueDepth;///<Command queue depth.

public:
/**
 * @brief Default constructor.
 */
    NVMe();

/**
 * @brief Constructor with parameters.
 * @param capacityGb Capacity.
 * @param pcieLanes Number of lanes.
 * @param queueDepth Queue depth.
 */ 
    NVMe(int capacityGb,int pcieLanes,int queueDepth);

/**
* @brief Calculates the read speed.
* @return Speed in MB/s.
*/
    int readSpeed();
};