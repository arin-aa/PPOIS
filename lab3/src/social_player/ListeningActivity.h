/**
 * @file ListeningActivity.h
 * @brief Declaration of the ListeningActivity class.
 */
#pragma once
#include <string>

class Track;

/**
 * @class ListeningActivity
 * @brief Record that a user listened to a track at some moment.
 */
class ListeningActivity{
private:
    std::string userId;///<Identifier of the listener.
    Track* track;///<Pointer to the track that was listened to.
    long long listenedAt;///<Moment of listening (ms).

public:
/**
 * @brief Constructor with parameters.
 * @param userId Identifier of the listener.
 * @param track Pointer to the track.
 * @param listenedAt Moment of listening (ms).
 */
    ListeningActivity(const std::string& userId,Track* track,long long listenedAt);

/**
 * @brief Checks whether the activity happened recently.
 * @param now Current time (ms).
 * @param windowMs Length of the period that counts as recent (ms).
 * @return true if the activity is not older than the window.
 */
    bool isRecent(long long now,long long windowMs) const;

/**
 * @brief Returns the listener.
 * @return Identifier of the listener.
 */
    const std::string& getUserId() const;

/**
 * @brief Returns the moment of listening.
 * @return Time in milliseconds.
 */
    long long getListenedAt() const;
};