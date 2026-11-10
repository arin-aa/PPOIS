/**
 * @file NotificationSettings.h
 * @brief Declaration of the NotificationSettings class.
 */
#pragma once

/**
 * @class NotificationSettings
 * @brief Choice of notifications that the user wants to receive.
 */
class NotificationSettings{
private:
    bool enabled;///<Master switch of all notifications.
    bool newReleases;///<Whether notifications about new releases are wanted.

public:
/**
 * @brief Constructor with parameters.
 * @param enabled Master switch of all notifications.
 * @param newReleases Whether notifications about new releases are wanted.
 */
    NotificationSettings(bool enabled,bool newReleases);

/**
 * @brief Turns all notifications off.
 */
    void muteAll();

/**
 * @brief Tells whether notifications are enabled at all.
 * @return Value of the master switch.
 */
    bool getEnabled() const;

/**
 * @brief Tells whether notifications about new releases are wanted.
 * @return true if they are wanted.
 */
    bool getNewReleases() const;
};