/**
 * @file CompatibilityChecker.h
 * @brief Declaration of the CompatibilityChecker class.
 */
#pragma once

/**
 * @class CompatibilityChecker
 * @brief Class for checking power supply and power consumption compatibility.
 * 
 * Allows calculating the power reserve and throwing an exception 
 * if the reserve is below the minimum allowed.
 */
class CompatibilityChecker{
private:
    bool strictMode;///<Strict checking mode flag.
    int checksDone;///<Counter of performed checks.
    int minReserveWatts;///<Minimum allowed power reserve in watts.

public:
/**
 * @brief Default constructor.
 */
    CompatibilityChecker();

/**
 * @brief Constructor with parameters.
 * @param strictMode Whether to enable strict mode.
 * @param minReserveWatts Minimum power reserve.
 */
    CompatibilityChecker(bool strictMode,int minReserveWatts);

/**
 * @brief Checks whether the power supply capacity is sufficient.
 * @param supplyWatts Power supply wattage.
 * @param demandWatts Required wattage.
 * @return Power reserve (difference between supplyWatts and demandWatts).
 * @exception InsufficientPowerException if in strict mode the reserve is less than the minimum.
 */
    int checkPower(int supplyWatts,int demandWatts);
};