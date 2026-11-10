/**
 * @file Device.h
 * @brief Declaration of the Device class.
 */
#pragma once
#include <string>

/**
 * @class Device
 * @brief Phone, computer or speaker where the user listens to music.
 */
class Device{
private:
    std::string id;///<Unique identifier of the device.
    std::string name;///<Name given by the user.
    std::string platform;///<Operating system, for example "android".
    long long lastActiveAt;///<Moment of the last activity (ms).
    std::string syncToken;///<Token of the last successful synchronization.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param name Name given by the user.
 * @param platform Operating system.
 * @param lastActiveAt Moment of the last activity (ms).
 * @param syncToken Token of the last synchronization.
 */
    Device(const std::string& id,const std::string& name,const std::string& platform,long long lastActiveAt,
           const std::string& syncToken);

/**
 * @brief Marks the device as active now.
 * @param now Current time (ms).
 */
    void touch(long long now);

/**
 * @brief Checks whether the device was active recently.
 * @param now Current time (ms).
 * @return true if the last activity is not older than five minutes.
 */
    bool isOnline(long long now) const;
};