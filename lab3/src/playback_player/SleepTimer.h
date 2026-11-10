/**
 * @file SleepTimer.h
 * @brief Declaration of the SleepTimer class.
 */
#pragma once

/**
 * @class SleepTimer
 * @brief Countdown that tells when the playback must be stopped.
 */
class SleepTimer{
private:
    int durationMs;///<Length of the countdown in milliseconds.
    int remainingMs;///<Time left in milliseconds.

public:
/**
 * @brief Default constructor. The timer is not running.
 */
    SleepTimer();

/**
 * @brief Starts the countdown.
 * @param newDurationMs Length of the countdown in milliseconds.
 * @exception PlaybackException if the length is not positive.
 */
    void start(int newDurationMs);

/**
 * @brief Returns the time left.
 * @return Time left in milliseconds.
 */
    int getRemainingMs() const;
};