/**
 * @file Webcam.h
 * @brief Declaration of the Webcam class.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Webcam
 * @brief Webcam class, inheriting from Peripheral.
 */
class Webcam:public Peripheral{
private:
    int heightPx;///<Video height in pixels.
    int fps;///<Frame rate per second.
    int recordedSeconds;///<Total recording time in seconds.

public:
/**
 * @brief Default constructor.
 */
    Webcam();

/**
 * @brief Constructor with video parameters specified.
 * @param heightPx Frame height.
 * @param fps Frame rate.
 */
    Webcam(int heightPx,int fps);

/**
 * @brief Records video.
 * @param seconds Recording duration.
 * @return Amount of recorded data in kilobytes.
 */
    int record(int seconds);
};