/**
 * @file PlaybackState.h
 * @brief Declaration of the PlaybackState class.
 */
#pragma once

class Track;

/**
 * @class PlaybackState
 * @brief Snapshot of what the player is doing now.
 */
class PlaybackState{
private:
    Track* currentTrack;///<Pointer to the loaded track, may be null.
    int positionMs;///<Playback position in milliseconds.
    bool playing;///<Whether the track is playing.
    bool shuffle;///<Whether shuffle mode is on.

public:
/**
 * @brief Default constructor. There is no track.
 */
    PlaybackState();

/**
 * @brief Moves the position, never beyond the end of the current track.
 * @param newPositionMs New position in milliseconds.
 * @return Position that was actually set.
 * @exception PlaybackException if the position is negative.
 */
    int updatePosition(int newPositionMs);

/**
 * @brief Switches shuffle mode.
 * @return true if shuffle is on after the switch.
 */
    bool toggleShuffle();

/**
 * @brief Sets the current track.
 * @param track Pointer to the new current track.
 */
    void setTrack(Track* track);

/**
 * @brief Sets the playing flag.
 * @param isPlaying New value.
 */
    void setPlaying(bool isPlaying);

/**
 * @brief Returns the current track.
 * @return Pointer to the track, may be null.
 */
    Track* getCurrentTrack() const;

/**
 * @brief Returns the position.
 * @return Position in milliseconds.
 */
    int getPositionMs() const;

/**
 * @brief Tells whether the track is playing.
 * @return true while playing.
 */
    bool getPlaying() const;
};