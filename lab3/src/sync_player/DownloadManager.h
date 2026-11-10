/**
 * @file DownloadManager.h
 * @brief Declaration of the DownloadManager class.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class DownloadManager
 * @brief Controls downloads of tracks for offline listening.
 *
 * Only a limited number of downloads run at the same time, the others wait in a queue.
 */
class DownloadManager{
private:
    std::vector<int> queue;///<Identifiers of tracks that wait for their turn.
    int activeCount;///<Number of downloads in progress.
    int maxConcurrent;///<Largest number of downloads that may run together.

public:
/**
 * @brief Constructor that creates a manager with no downloads.
 * @param maxConcurrent Largest number of simultaneous downloads.
 */
    explicit DownloadManager(int maxConcurrent);

/**
 * @brief Starts downloading a track or puts it into the queue.
 * @param trackId Identifier of the track.
 * @param url Address of the file.
 * @return true if the download started, false if it is waiting in the queue.
 * @exception DownloadException if the address is empty.
 */
    bool start(int trackId,const std::string& url);

/**
 * @brief Cancels a download.
 *
 * A waiting track is removed from the queue. Otherwise a running download is stopped
 * and the first waiting track takes its place.
 * @param trackId Identifier of the track.
 * @exception TrackNotFoundException if nothing is waiting or running.
 */
    void cancel(int trackId);

/**
 * @brief Counts the waiting tracks.
 * @return Length of the queue.
 */
    int getQueueSize() const;

/**
 * @brief Counts the running downloads.
 * @return Number of downloads in progress.
 */
    int getActiveCount() const;
};