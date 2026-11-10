/**
 * @file Track.h
 * @brief Declaration of the Track class.
 */
#pragma once
#include <string>
#include <vector>

class AudioFile;

/**
 * @class Track
 * @brief Single song of the catalog.
 */
class Track{
private:
    int id;///<Unique identifier of the track.
    std::string title;///<Title of the song.
    int artistId;///<Identifier of the performer.
    int albumId;///<Identifier of the album.
    int durationMs;///<Length of the song in milliseconds.
    AudioFile* audioFile;///<Pointer to the file with the sound, may be null.
    std::vector<int> genreIds;///<Identifiers of the genres of the song.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param title Title of the song.
 * @param artistId Identifier of the performer.
 * @param albumId Identifier of the album.
 * @param durationMs Length of the song in milliseconds.
 * @param audioFile Pointer to the file with the sound, may be null.
 * @param genreIds Identifiers of the genres.
 */
    Track(int id,const std::string& title,int artistId,int albumId,int durationMs,AudioFile* audioFile,
          const std::vector<int>& genreIds=std::vector<int>());

/**
 * @brief Checks whether the track can be played.
 * @return true if the track has an audio file and a positive duration.
 */
    bool isPlayable() const;

/**
 * @brief Checks whether the title contains a text, ignoring letter case.
 * @param query Text to look for.
 * @return true if the title contains the text.
 */
    bool matchesQuery(const std::string& query) const;

/**
 * @brief Returns the identifier.
 * @return Track identifier.
 */
    int getId() const;

/**
 * @brief Returns the title.
 * @return Title of the song.
 */
    const std::string& getTitle() const;

/**
 * @brief Returns the identifier of the performer.
 * @return Artist identifier.
 */
    int getArtistId() const;

/**
 * @brief Returns the length of the song.
 * @return Duration in milliseconds.
 */
    int getDurationMs() const;

/**
 * @brief Returns the file with the sound.
 * @return Pointer to the audio file, may be null.
 */
    AudioFile* getAudioFile() const;

/**
 * @brief Returns the genres of the song.
 * @return Identifiers of the genres.
 */
    const std::vector<int>& getGenreIds() const;
};