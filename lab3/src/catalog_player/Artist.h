/**
 * @file Artist.h
 * @brief Declaration of the Artist class.
 */
#pragma once
#include <string>
#include <vector>

class MediaLibrary;

/**
 * @class Artist
 * @brief Performer or band.
 */
class Artist{
private:
    int id;///<Unique identifier of the artist.
    std::string name;///<Name of the artist.
    std::vector<int> albumIds;///<Identifiers of the albums of the artist.
    std::string imageUrl;///<Address of the photo of the artist.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param name Name of the artist.
 * @param albumIds Identifiers of the albums.
 * @param imageUrl Address of the photo.
 */
    Artist(int id,const std::string& name,const std::vector<int>& albumIds,const std::string& imageUrl);

/**
 * @brief Counts the tracks in all albums of the artist that are known to a library.
 * @param library Library that stores the albums.
 * @return Number of tracks.
 */
    int getTrackCount(const MediaLibrary* library) const;

/**
 * @brief Checks whether the artist has albums.
 * @return true if at least one album is known.
 */
    bool hasAlbums() const;

/**
 * @brief Returns the name.
 * @return Artist name.
 */
    const std::string& getName() const;
};