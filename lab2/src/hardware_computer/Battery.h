/**
 * @file Battery.h
 * @brief Declaration of the Battery class.
 */
#pragma once

/**
 * @class Battery
 * @brief Class describing a rechargeable battery.
 */
class Battery{
private:
    int capacityWh;///<Total battery capacity in watt-hours.
    int chargePercent;///<Current charge level in percent.
    int cycles;///<Number of full charge cycles.

public:
/**
 * @brief Default constructor.
 */
    Battery();

/**
 * @brief Constructor with parameters.
 * @param capacityWh Capacity.
 * @param chargePercent Initial charge.
 */
    Battery(int capacityWh,int chargePercent);

/**
 * @brief Charges the battery.
 * @param percent Number of percent to charge.
 * @return Resulting charge level.
 */
    int charge(int percent);

/**
 * @brief Calculates battery life at a given power consumption.
 * @param watts Power consumption of the device.
 * @return Operating time in minutes.
 */
    int runtimeMinutes(int watts);
};