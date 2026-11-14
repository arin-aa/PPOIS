/**
 * @file ContentCatalog.h
 * @brief Declaration of the ContentCatalog class.
 */
#pragma once
#include <string>
#include <vector>

class MediaLibrary;
class Track;

/**
 * @class ContentCatalog
 * @brief Fast title search over a media library based on prepared titles.
 *
 * The index must be rebuilt after tracks are added to the library.
 */
class ContentCatalog{
private:
    MediaLibrary* library;///<Pointer to the library that is indexed.
    std::vector<std::string> normalizedTitles;///<Normalized titles in the order of the library tracks.

public:
/**
 * @brief Constructor with a library. The titles are not prepared until the index is rebuilt.
 * @param library Pointer to the library to index.
 */
    explicit ContentCatalog(MediaLibrary* library);

/**
 * @brief Finds tracks whose normalized titles contain the normalized query.
 * @param query Search text.
 * @return Matching tracks, empty if the query has no words.
 */
    std::vector<Track*> searchByTitle(const std::string& query) const;

/**
 * @brief Prepares the normalized titles of the current tracks of the library.
 * @return Number of prepared titles.
 */
    int rebuildIndex();

/**
 * @brief Returns the indexed library.
 * @return Pointer to the library.
 */
    MediaLibrary* getLibrary() const;
};