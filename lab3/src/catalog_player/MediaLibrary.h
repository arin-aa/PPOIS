/**
 * @file MediaLibrary.h
 * @brief Declaration of the MediaLibrary class.
 */
#pragma once
#include <string>
#include <vector>

class Album;
class Artist;
class Genre;
class Track;

/**
 * @class MediaLibrary
 * @brief Storage of all tracks, albums, artists and genres known to the player.
 *
 * The library does not own the objects, it only keeps pointers to them.
 */
class MediaLibrary{
private:
    std::vector<Track*> tracks;///<All tracks of the library.
    std::vector<Album*> albums;///<All albums of the library.
    std::vector<Artist*> artists;///<All artists of the library.
    std::vector<Genre*> genres;///<All genres of the library.

public:
/**
 * @brief Constructor with the initial content.
 * @param tracks Tracks of the library.
 * @param albums Albums of the library.
 * @param artists Artists of the library.
 * @param genres Genres of the library.
 */
    explicit MediaLibrary(const std::vector<Track*>& tracks=std::vector<Track*>(),
                          const std::vector<Album*>& albums=std::vector<Album*>(),
                          const std::vector<Artist*>& artists=std::vector<Artist*>(),
                          const std::vector<Genre*>& genres=std::vector<Genre*>());

/**
 * @brief Adds a track.
 * @param track Track to add.
 * @return true if the track was added, false if a track with the same identifier already exists.
 */
    bool addTrack(Track* track);

/**
 * @brief Finds a track by its identifier.
 * @param trackId Identifier of the track.
 * @return Pointer to the track, null if the library has no such track.
 */
    Track* findTrackById(int trackId) const;

/**
 * @brief Finds all tracks of a genre.
 * @param genreId Identifier of the genre.
 * @return Tracks that belong to the genre.
 */
    std::vector<Track*> findByGenre(int genreId) const;

/**
 * @brief Finds all tracks whose title contains a text.
 * @param query Text to look for, letter case is ignored.
 * @return Matching tracks.
 */
    std::vector<Track*> findByTitle(const std::string& query) const;

/**
 * @brief Finds all albums whose title contains a text.
 * @param text Text to look for, letter case is important.
 * @return Albums that contain the text, in library order.
 */
    std::vector<Album*> findAlbumsByTitle(const std::string& text) const;

/**
 * @brief Finds all artists whose name contains a text.
 * @param text Text to look for, letter case is important.
 * @return Artists that contain the text, in library order.
 */
    std::vector<Artist*> findArtistsByName(const std::string& text) const;

/**
 * @brief Returns all tracks.
 * @return Tracks of the library.
 */
    const std::vector<Track*>& getTracks() const;

/**
 * @brief Returns all albums.
 * @return Albums of the library.
 */
    const std::vector<Album*>& getAlbums() const;
};