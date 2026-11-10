/**
 * @file HDD.h
 * @brief Declaration of the HDD class.
 */

#pragma once
#include "Storage.h"

/**
 * @class HDD
 * @brief Hard disk drive class.
 */
class HDD:public Storage{
private:
    int rpm;///<Spindle speed
    int badSectors;///<Number of bad blocks
    int fragmentation;///<Fragmentation level

public:
/**
 * @brief Default constructor.
 */
    HDD();

/**
 * @brief Constructor with parameters.
 * @param capacityGb Capacity.
 * @param rpm Speed.
 * @param fragmentation Fragmentation.
 */
    HDD(int capacityGb,int rpm,int fragmentation);

/**
 * @brief Performs disk defragmentation.
 * @return Time spent in minutes.
 */
    int defragment();

/**
 * @brief Calculates the remaining disk life.
 * @return Percentage of remaining resource.
 */
    int lifeLeft() override;
};