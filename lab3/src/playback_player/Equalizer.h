/**
 * @file Equalizer.h
 * @brief Declaration of the Equalizer class.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class Equalizer
 * @brief Graphic equalizer with a fixed number of frequency bands.
 */
class Equalizer{
private:
    std::vector<int> bands;///<Gain of each band in decibels.
    bool enabled;///<Whether the equalizer changes the sound.

public:
/**
 * @brief Default constructor. All bands are at zero and the equalizer is disabled.
 */
    Equalizer();

/**
 * @brief Applies a named preset and enables the equalizer.
 * @param presetName "flat", "bass" or "treble".
 * @exception AudioEngineException if the preset is unknown.
 */
    void applyPreset(const std::string& presetName);

/**
 * @brief Sets the gain of one band.
 * @param bandIndex Index of the band.
 * @param gain Gain in decibels, from -12 to 12.
 * @exception AudioEngineException if the index or the gain is outside the allowed range.
 */
    void setBandGain(int bandIndex,int gain);

/**
 * @brief Returns the gain of one band.
 * @param bandIndex Index of the band.
 * @return Gain in decibels, zero if the index is outside the allowed range.
 */
    int getGain(int bandIndex) const;
};