/**
 * @file Sensor.h
 * @brief Declaration of the Sensor class.
 */
#pragma once

/**
 * @class Sensor
 * @brief Sensor class.
 */
class Sensor{
private:
    double value;///<Current reading.
    double threshold;///<Threshold value.
    int readings;///<Number of measurements.

public:
/**
 * @brief Default constructor.
 */
    Sensor();

/**
 * @brief Constructor with threshold.
 * @param threshold Threshold value.
 */
    explicit Sensor(double threshold);

/**
 * @brief Adds a new reading and calculates the average.
 * @param reading New value.
 */    
    void measure(double reading);

/**
 * @brief Calculates the margin to the threshold.
 * @return Difference between the threshold and the current value.
 */
    double margin();
};