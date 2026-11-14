/**
 * @file Laptop.h
 * @brief Declaration of the Laptop class.
 */
#pragma once
#include "Computer.h"

class Battery;

/**
 * @class Laptop
 * @brief Derived class representing a laptop.
 * 
 * Extends the base class Computer by adding a screen, a battery, and 
 * the ability to run on battery power.
 */
class Laptop:public Computer{
private:
    int screenInches;///<Screen diagonal in inches.
    int chargedMinutes;///<Number of minutes the battery is charged for.
    Battery* battery;///<Pointer to the battery object.

public:
/**
 * @brief Default constructor.
 */
    Laptop();

/**
 * @brief Constructor with parameters.
 * @param hostname Network name.
 * @param screenInches Screen diagonal.
 * @param battery Pointer to the battery.
 */
    Laptop(const std::string& hostname,int screenInches,Battery* battery);

/**
 * @brief Connects the laptop to charging.
 * @param minutes Charging time in minutes.
 * @return Current battery charge percentage.
 */
    int plugIn(int minutes);

/**
 * @brief Calculates the battery life.
 * @return Battery operation time in minutes.
 */   
    int batteryMinutes();

/**
 * @brief Overridden method for calculating power consumption.
 * Takes into account the power consumption of the screen and base components.
 * @return Power consumption in watts.
 */    
    int powerDraw() override;
};