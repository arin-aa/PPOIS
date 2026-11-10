/**
 * @file CrossfadeSettings.h
 * @brief Declaration of the CrossfadeSettings class.
 */
#pragma once

/**
 * @class CrossfadeSettings
 * @brief Smooth transition between two tracks.
 */
class CrossfadeSettings{
private:
    int durationMs;///<Length of the transition in milliseconds, zero means off.

public:
/**
 * @brief Constructor with a length.
 * @param durationMs Length of the transition in milliseconds.
 */
    explicit CrossfadeSettings(int durationMs=0);

/**
 * @brief Checks whether crossfade is on.
 * @return true if the length is positive.
 */
    bool isEnabled() const;
};