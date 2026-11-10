/**
 * @file SyncConflict.h
 * @brief Declaration of the SyncConflict class.
 */
#pragma once
#include <string>

/**
 * @class SyncConflict
 * @brief Difference between the local and the cloud version of the same data.
 *
 * A version is the moment when the data was changed last (ms).
 */
class SyncConflict{
private:
    std::string entityType;///<Kind of data, for example "playlists".
    long long localVersion;///<Version stored on the device.
    long long remoteVersion;///<Version stored in the cloud.

public:
/**
 * @brief Constructor with parameters.
 * @param entityType Kind of data.
 * @param localVersion Version stored on the device.
 * @param remoteVersion Version stored in the cloud.
 */
    SyncConflict(const std::string& entityType,long long localVersion,long long remoteVersion);

/**
 * @brief Chooses the version that must be kept.
 * @param strategy "local", "remote" or "newest".
 * @return Version that wins.
 * @exception SyncException if the strategy is unknown.
 */
    long long applyResolution(const std::string& strategy) const;
};