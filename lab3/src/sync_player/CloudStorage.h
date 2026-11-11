/**
 * @file CloudStorage.h
 * @brief Declaration of the CloudStorage class.
 */
#pragma once
#include <string>

const long long NEVER_SYNCED=0;///<Version of the cloud that has received nothing yet.

/**
 * @class CloudStorage
 * @brief Model of the cloud service that keeps the version of the user data.
 *
 * The version of the data is the moment when it was changed last (ms).
 * The cloud remembers the version of the last upload.
 */
class CloudStorage{
private:
    std::string apiUrl;///<Address of the service.
    std::string token;///<Access token, empty if the user is not authorized.
    long long lastSyncAt;///<Version of the last upload (ms), NEVER_SYNCED if nothing was uploaded.

public:
/**
 * @brief Constructor with parameters. Nothing is stored yet.
 * @param apiUrl Address of the service.
 * @param token Access token.
 */
    CloudStorage(const std::string& apiUrl,const std::string& token);

/**
 * @brief Reads the stored version of the data.
 * @param entityType Kind of data.
 * @return Stored version.
 * @exception SyncException if the user is not authorized or nothing is stored.
 */
    long long download(const std::string& entityType) const;

/**
 * @brief Stores a version of the data.
 * @param entityType Kind of data.
 * @param version Version to store.
 * @exception SyncException if the user is not authorized.
 */
    void upload(const std::string& entityType,long long version);

/**
 * @brief Returns the version of the last upload.
 * @return Version in milliseconds, zero if nothing was uploaded.
 */
    long long getLastSyncAt() const;
};