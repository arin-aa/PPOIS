/**
 * @file PlaylistItem.h
 * @brief Declaration of the PlaylistItem class.
 */
#pragma once

class Track;

/**
 * @class PlaylistItem
 * @brief Position of one track inside a playlist.
 */
class PlaylistItem{
private:
    Track* track;///<Pointer to the track placed in the playlist.
    int position;///<Zero-based position inside the playlist.

public:
/**
 * @brief Constructor with parameters.
 * @param track Pointer to the track.
 * @param position Zero-based position.
 */
    PlaylistItem(Track* track,int position);

/**
 * @brief Checks whether the item can be played.
 * @return true if the track is playable and the position is not negative.
 */
    bool isValid() const;

/**
 * @brief Changes the position of the item.
 * @param newPosition New zero-based position.
 */
    void setPosition(int newPosition);

/**
 * @brief Returns the track.
 * @return Pointer to the track.
 */
    Track* getTrack() const;

/**
 * @brief Returns the position.
 * @return Zero-based position.
 */
    int getPosition() const;
};