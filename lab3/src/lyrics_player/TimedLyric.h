/**
 * @file TimedLyric.h
 * @brief Declaration of the TimedLyric class.
 */
#pragma once
#include <string>

/**
 * @class TimedLyric
 * @brief One line of lyrics that is shown from a given moment.
 */
class TimedLyric{
private:
    int startMs;///<Moment when the line appears, from the start of the track (ms).
    std::string text;///<Text of the line.

public:
/**
 * @brief Constructor with parameters.
 * @param startMs Moment when the line appears (ms).
 * @param text Text of the line.
 */
    TimedLyric(int startMs,const std::string& text);

/**
 * @brief Checks whether the line is shown at a moment.
 * @param positionMs Playback position (ms).
 * @param endMs Moment when the next line appears (ms).
 * @return true if the position is not before the start and is before the end.
 */
    bool isActiveAt(int positionMs,int endMs) const;

/**
 * @brief Returns the start moment.
 * @return Time in milliseconds.
 */
    int getStartMs() const;

/**
 * @brief Returns the text.
 * @return Text of the line.
 */
    const std::string& getText() const;
};