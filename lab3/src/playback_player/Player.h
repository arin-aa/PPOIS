/**
 * @file Player.h
 * @brief Declaration of the Player class.
 */
#pragma once

class AudioEngine;
class Equalizer;
class PlaybackHistory;
class PlaybackState;
class Queue;

/**
 * @class Player
 * @brief Main component that connects the queue, the audio engine, the state and the history.
 */
class Player{
private:
    AudioEngine* engine;///<Pointer to the engine that produces the sound.
    Queue* queue;///<Pointer to the queue of tracks to play.
    PlaybackState* state;///<Pointer to the current state of the playback.
    PlaybackHistory* history;///<Pointer to the history that receives finished sessions.
    Equalizer* equalizer;///<Pointer to the equalizer applied to the sound.
    int volume;///<Volume level from 0 to 100.

public:
/**
 * @brief Constructor with the components of the player. The volume is taken from the engine.
 * @param engine Pointer to the engine.
 * @param queue Pointer to the queue.
 * @param state Pointer to the state of the playback.
 * @param history Pointer to the history of listening.
 * @param equalizer Pointer to the equalizer.
 */
    Player(AudioEngine* engine,Queue* queue,PlaybackState* state,PlaybackHistory* history,Equalizer* equalizer);

/**
 * @brief Plays the current track of the queue, or resumes it after a pause.
 * @exception PlaybackException if the queue is empty or the track cannot be played.
 */
    void play();

/**
 * @brief Pauses the playback and keeps the position.
 */
    void pause();

/**
 * @brief Stops the playback, records the session and rewinds.
 * @param now Current time (ms).
 */
    void stop(long long now);

/**
 * @brief Records the finished session and starts the next track.
 * @param now Current time (ms).
 * @exception PlaybackException if there is no next track.
 */
    void next(long long now);

/**
 * @brief Records the finished session and starts the previous track.
 * @param now Current time (ms).
 * @exception PlaybackException if the queue is empty.
 */
    void previous(long long now);

/**
 * @brief Jumps to a position of the current track.
 * @param positionMs Position in milliseconds.
 * @exception PlaybackException if no track is loaded or the position is outside the track.
 */
    void seek(int positionMs);
};




