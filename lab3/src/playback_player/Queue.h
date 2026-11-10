/**
 * @file Queue.h
 * @brief Declaration of the Queue class.
 */
#pragma once
#include <string>
#include <vector>

class Track;

/**
 * @class Queue
 * @brief Ordered list of tracks that will be played, with a current position.
 *
 * The repeat mode is "off", "one" or "all".
 */
class Queue{
private:
    std::vector<Track*> items;///<Tracks in playback order.
    int currentIndex;///<Index of the current track.
    std::string repeatMode;///<What happens when the end is reached.

public:
/**
 * @brief Constructor that creates an empty queue.
 * @param repeatMode Repeat mode: "off", "one" or "all".
 */
    explicit Queue(const std::string& repeatMode="off");

/**
 * @brief Moves to the next track according to the repeat mode.
 * @return Pointer to the new current track.
 * @exception PlaybackException if the queue is empty or the end is reached with repeat off.
 */
    Track* next();

/**
 * @brief Moves to the previous track according to the repeat mode.
 * @return Pointer to the new current track.
 * @exception PlaybackException if the queue is empty.
 */
    Track* previous();

/**
 * @brief Adds a track to the end of the queue.
 * @param track Pointer to the track.
 */
    void add(Track* track);

/**
 * @brief Returns the current track without moving.
 * @return Pointer to the current track.
 * @exception PlaybackException if the queue is empty.
 */
    Track* getCurrent() const;
};