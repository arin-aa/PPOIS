/**
 * @file AudioEngine.h
 * @brief Declaration of the AudioEngine class.
 */
#pragma once

class AudioFile;

/**
 * @class AudioEngine
 * @brief Low-level component that holds the loaded file and the playback position.
 */
class AudioEngine{
private:
    AudioFile* currentFile;///<Pointer to the loaded file, null if nothing is loaded.
    int positionMs;///<Playback position in milliseconds.
    int volume;///<Volume level from 0 to 100.
    bool playing;///<Whether the sound is being produced.

public:
/**
 * @brief Default constructor. Nothing is loaded.
 */
    AudioEngine();

/**
 * @brief Loads a file and rewinds to the beginning.
 * @param file Pointer to the file to load.
 * @exception AudioEngineException if the file is missing or its bitrate is not positive.
 */
    void load(AudioFile* file);

/**
 * @brief Starts or resumes the sound.
 * @exception AudioEngineException if no file is loaded.
 */
    void play();

/**
 * @brief Pauses the sound and keeps the position.
 */
    void pause();

/**
 * @brief Moves the playback position.
 * @param newPositionMs New position in milliseconds, a negative value is replaced by zero.
 */
    void setPosition(int newPositionMs);

/**
 * @brief Returns the loaded file.
 * @return Pointer to the file, may be null.
 */
    AudioFile* getCurrentFile() const;

/**
 * @brief Returns the volume.
 * @return Volume level.
 */
    int getVolume() const;

/**
 * @brief Tells whether the sound is being produced.
 * @return true while playing.
 */
    bool getPlaying() const;
};