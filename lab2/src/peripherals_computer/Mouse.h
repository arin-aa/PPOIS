/**
 * @file Mouse.h
 * @brief Declaration of the Mouse class.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Mouse
 * @brief Computer mouse class, inheriting from Peripheral.
 */
class Mouse:public Peripheral{
private:
    int dpi;///<Current mouse sensitivity.
    int clicks;///<Click counter.

public:
/**
 * @brief Default constructor.
 */
    Mouse();

/**
 * @brief Constructor with sensitivity specified.
 * @param dpi Initial DPI value.
 */
    explicit Mouse(int dpi);
     
/** 
 * @brief Changes the mouse sensitivity.
 * @param newDpi New DPI value.
 * @return The set DPI value.
 * @exception InvalidConfigurationException if the DPI is outside the allowed range.
 */
    int changeDpi(int newDpi);

/**
 * @brief Simulates a mouse click.
 * @return Total number of clicks over all time.
 */
    int click();
};