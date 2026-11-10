/**
 * @file OfflineCache.h
 * @brief Declaration of the OfflineCache class.
 */
#pragma once
#include <map>
#include <utility>

/**
 * @class OfflineCache
 * @brief Limited storage for tracks that can be played without a network.
 *
 * When there is no room for a new file the oldest files are removed.
 */
class OfflineCache{
private:
    std::map<int,std::pair<long long,long long>> entries;///<Size in bytes and storing time (ms) by track identifier.
    long long maxSize;///<Capacity of the cache in bytes.
    long long ttl;///<Time after which a stored file is not valid anymore (ms).

public:
/**
 * @brief Constructor that creates an empty cache.
 * @param maxSize Capacity in bytes.
 * @param ttl Time to live of a file in milliseconds.
 */
    OfflineCache(long long maxSize,long long ttl);

/**
 * @brief Stores a file, removing the oldest files if the cache is full.
 * @param trackId Identifier of the track.
 * @param sizeBytes Size of the file in bytes.
 * @param now Current time (ms).
 * @exception DownloadException if the file is larger than the whole cache.
 */
    void put(int trackId,long long sizeBytes,long long now);

/**
 * @brief Reads a stored file.
 * @param trackId Identifier of the track.
 * @param now Current time (ms).
 * @return Size of the stored file in bytes.
 * @exception TrackNotFoundException if the file is missing or expired, an expired file is removed.
 */
    long long get(int trackId,long long now);
};