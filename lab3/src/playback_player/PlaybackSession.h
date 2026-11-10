/**
 * @file PlaybackSession.h
 * @brief Declaration of the PlaybackSession class.
 */
#pragma once

class Track;

/**
 * @class PlaybackSession
 * @brief One listening of one track.
 */
class PlaybackSession{
private:
    Track* track;///<Pointer to the track that was played.
    long long startedAt;///<Moment when the listening started (ms).
    int listenedMs;///<Time the track was actually listened to (ms).

public:
/**
 * @brief Constructor for a session that has not finished yet.
 * @param track Pointer to the track.
 * @param startedAt Moment when the listening started (ms).
 */
    PlaybackSession(Track* track,long long startedAt);

/**
 * @brief Finishes the session and calculates the listened time.
 *
 * The listened time cannot be longer than the track.
 * @param endedAt Moment when the listening ended (ms).
 * @return Listened time in milliseconds.
 */
    int finish(long long endedAt);

/**
 * @brief Checks whether most of the track was listened to.
 * @return true if at least 90 percent of the track was played.
 */
    bool isCompleted() const;

/**
 * @brief Returns the track.
 * @return Pointer to the track.
 */
    Track* getTrack() const;

/**
 * @brief Returns the listened time.
 * @return Time in milliseconds.
 */
    int getListenedMs() const;
};