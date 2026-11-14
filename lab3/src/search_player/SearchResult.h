/**
 * @file SearchResult.h
 * @brief Declaration of the SearchResult class.
 */
#pragma once
#include <string>
#include <vector>

class Album;
class Artist;
class Track;

/**
 * @class SearchResult
 * @brief Everything that was found for one query.
 */
class SearchResult{
protected:
    std::vector<Track*> tracks;///<Found tracks.
    std::vector<Album*> albums;///<Found albums.
    std::vector<Artist*> artists;///<Found artists.

public:
/**
 * @brief Constructor with parameters.
 * @param tracks Found tracks.
 * @param albums Found albums.
 * @param artists Found artists.
 */
    SearchResult(const std::vector<Track*>& tracks,const std::vector<Album*>& albums,const std::vector<Artist*>& artists);

/**
 * @brief Finds the best match: the first track, otherwise the first album, otherwise the first artist.
 * @return Title or name of the best match, empty string if nothing was found.
 */
    std::string getTopResult() const;

/**
 * @brief Counts all found items.
 * @return Number of tracks, albums and artists together.
 */
    int getTotalCount() const;
};