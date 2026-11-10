/**
 * @file Monitor.h
 * @brief Declaration of the Monitor class.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Monitor
 * @brief Monitor class, inheriting from Peripheral.
 */
class Monitor:public Peripheral{
private:
    int widthPx;///<Screen width in pixels.
    int heightPx;///<Screen height in pixels.
    int brightness; ///<Current brightness level.

public:
/**
 * @brief Default constructor.
 */
    Monitor();

/**
 * @brief Constructor with screen resolution specified.
 * @param widthPx Width in pixels.
 * @param heightPx Height in pixels.
 */
    Monitor(int widthPx,int heightPx);

/**
 * @brief Changes the brightness level.
 * @param delta Increase or decrease in brightness.
 * @return Resulting brightness level within the range from 0 to 100.
 */
    int adjustBrightness(int delta);

/**
 * @brief Calculates the screen resolution in megapixels.
 * @return Number of megapixels.
 */
    double megapixels();
};