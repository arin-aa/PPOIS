/**
 * @file Playlist.h
 * @brief Declaration of the Playlist class.
 */
#pragma once
#include <string>
#include <vector>
#include "PlaylistItem.h"

class Track;

/**
 * @class Playlist
 * @brief Ordered list of tracks created by a user.
 */
class Playlist{
private:
    int id;///<Unique identifier of the playlist.
    std::string ownerId;///<Identifier of the user who owns the playlist.
    std::string title;///<Title of the playlist.
    std::string description;///<Free text description.
    std::vector<PlaylistItem> items;///<Items in playback order.

public:
/**
 * @brief Constructor that creates an empty playlist.
 * @param id Unique identifier.
 * @param ownerId Identifier of the owner.
 * @param title Title of the playlist.
 * @param description Free text description.
 */
    Playlist(int id,const std::string& ownerId,const std::string& title,const std::string& description);

/**
 * @brief Adds a track to the end of the playlist.
 * @param track Pointer to the track.
 * @exception PlaylistException if the track cannot be played or the playlist is full.
 */
    void addTrack(Track* track);

/**
 * @brief Removes a track from the playlist and renumbers the other items.
 * @param trackId Identifier of the track.
 * @exception TrackNotFoundException if the track is not in the playlist.
 */
    void removeTrack(int trackId);

/**
 * @brief Sums the durations of all tracks.
 * @return Total duration in milliseconds.
 */
    long long getTotalDuration() const;

/**
 * @brief Returns the identifier.
 * @return Playlist identifier.
 */
    int getId() const;

/**
 * @brief Returns the identifier of the owner.
 * @return Owner identifier.
 */
    const std::string& getOwnerId() const;

/**
 * @brief Returns the title.
 * @return Playlist title.
 */
    const std::string& getTitle() const;

/**
 * @brief Returns the items.
 * @return Items in playback order.
 */
    const std::vector<PlaylistItem>& getItems() const;
};