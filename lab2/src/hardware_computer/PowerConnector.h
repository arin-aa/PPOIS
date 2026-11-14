/**
 * @file PowerConnector.h
 * @brief Declaration of the PowerConnector class.
 */
#pragma once

/**
 * @class PowerConnector
 * @brief Power connector class.
 */
class PowerConnector{
private:
    int pinCount;///<Number of pins.
    bool isPlugged;///<Connection flag.

public:
/**
 * @brief Default constructor.
 */
    PowerConnector();

/**
 * @brief Constructor with pin count specified.
 * @param pinCount Number of pins.
 */
    explicit PowerConnector(int pinCount);

/**
 * @brief Connects the connector.
 * @return Number of pins.
 * @exception InvalidConfigurationException if already connected.
 */ 
    int attach();
};