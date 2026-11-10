/**
 * @file SyncService.h
 * @brief Declaration of the SyncService class.
 */
#pragma once
#include <string>

class CloudStorage;
class SyncConflict;

/**
 * @class SyncService
 * @brief Keeps the data of a device and the cloud equal.
 */
class SyncService{
private:
    CloudStorage* cloud;///<Pointer to the cloud that stores the data.

public:
/**
 * @brief Constructor with a cloud.
 * @param cloud Pointer to the cloud.
 */
    explicit SyncService(CloudStorage* cloud);

/**
 * @brief Synchronizes one kind of data with the cloud.
 *
 * Missing data is uploaded. If the versions differ, the conflict is resolved by the strategy
 * and the cloud is updated when it does not hold the winning version.
 * @param entityType Kind of data.
 * @param localVersion Version stored on the device (ms).
 * @param strategy "local", "remote" or "newest".
 * @return Version that is stored on both sides after the synchronization.
 * @exception SyncException if the cloud rejects the request or the strategy is unknown.
 */
    long long sync(const std::string& entityType,long long localVersion,const std::string& strategy);

/**
 * @brief Chooses the winning version of a conflict.
 * @param conflict Conflict to resolve.
 * @param strategy "local", "remote" or "newest".
 * @return Version that wins.
 * @exception SyncException if the strategy is unknown.
 */
    long long resolveConflict(const SyncConflict& conflict,const std::string& strategy) const;
};