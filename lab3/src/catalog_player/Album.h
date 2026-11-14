/**
 * @file Album.h
 * @brief Declaration of the Album class.
 */
#pragma once
#include <string>
#include <vector>

class MediaLibrary;

/**
 * @class Album
 * @brief Collection of tracks released together.
 */
class Album{
private:
    int id;///<Unique identifier of the album.
    std::string title;///<Title of the album.
    int artistId;///<Identifier of the performer.
    std::vector<int> trackIds;///<Identifiers of the tracks in release order.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param title Title of the album.
 * @param artistId Identifier of the performer.
 * @param trackIds Identifiers of the tracks in release order.
 */
    Album(int id,const std::string& title,int artistId,const std::vector<int>& trackIds);

/**
 * @brief Sums the durations of all tracks of the album.
 * @param library Library that stores the tracks.
 * @return Total duration in milliseconds.
 * @exception TrackNotFoundException if a track of the album is missing in the library.
 */
    long long getTotalDuration(const MediaLibrary* library) const;

/**
 * @brief Counts the tracks of the album.
 * @return Number of tracks.
 */
    int getTrackCount() const;

/**
 * @brief Returns the identifier.
 * @return Album identifier.
 */
    int getId() const;

/**
 * @brief Returns the title.
 * @return Album title.
 */
    const std::string& getTitle() const;
};