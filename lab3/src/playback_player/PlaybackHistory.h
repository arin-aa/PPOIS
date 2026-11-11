/**
 * @file PlaybackHistory.h
 * @brief Declaration of the PlaybackHistory class.
 */
#pragma once
#include <string>
#include <vector>
#include "PlaybackSession.h"

/**
 * @class PlaybackHistory
 * @brief Record of what a user listened to.
 */
class PlaybackHistory{
private:
    std::vector<PlaybackSession> sessions;///<Sessions from the oldest to the newest.
    std::string userId;///<Identifier of the owner.

public:
/**
 * @brief Constructor that creates an empty history.
 * @param userId Identifier of the owner.
 */
    explicit PlaybackHistory(const std::string& userId);

/**
 * @brief Adds a session. When the history is full the oldest session is dropped.
 * @param session Session to add.
 */
    void add(const PlaybackSession& session);

/**
 * @brief Returns the newest sessions.
 * @param count Maximum number of sessions.
 * @return Sessions from the newest to the oldest.
 */
    std::vector<PlaybackSession> getRecent(int count) const;

/**
 * @brief Returns all sessions.
 * @return Sessions from the oldest to the newest.
 */
    const std::vector<PlaybackSession>& getSessions() const;
};