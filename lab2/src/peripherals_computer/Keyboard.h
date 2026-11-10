/**
 * @file Keyboard.h
 * @brief Declaration of the Keyboard class.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Keyboard
 * @brief Keyboard class, inheriting from Peripheral.
 */
class Keyboard:public Peripheral{
private:
    std::string layout;///<Current keyboard layout.
    int keyPresses;///<Key press counter.

public:
/**
 * @brief Default constructor.
 */
    Keyboard();

/**
 * @brief Constructor with layout specified.
 * @param layout Initial layout.
 */
    explicit Keyboard(const std::string& layout);

/**
 * @brief Switches the keyboard layout.
 * @param newLayout New layout ("EN", "RU", "DE").
 * @exception InvalidConfigurationException if the layout is not supported.
 */
    void switchLayout(const std::string& newLayout);

/**
 * @brief Simulates key presses.
 * @param count Number of presses.
 * @return Total number of presses over all time.
 */
    int press(int count);
};