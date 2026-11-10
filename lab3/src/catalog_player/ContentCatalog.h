/**
 * @file ContentCatalog.h
 * @brief Declaration of the ContentCatalog class.
 */
#pragma once
#include <map>
#include <string>
#include <vector>

class MediaLibrary;
class Track;

/**
 * @class ContentCatalog
 * @brief Fast title search over a media library based on a word index.
 *
 * The index must be rebuilt after tracks are added to the library.
 */
class ContentCatalog{
private:
    MediaLibrary* library;///<Pointer to the library that is indexed.
    std::map<std::string,std::vector<int>> index;///<Track identifiers by lower-case title word.

public:
/**
 * @brief Constructor with a library. The index is empty until it is rebuilt.
 * @param library Pointer to the library to index.
 */
    explicit ContentCatalog(MediaLibrary* library);

/**
 * @brief Finds tracks whose titles contain words starting with every word of the query.
 * @param query Search text.
 * @return Matching tracks, empty if the query has no words.
 */
    std::vector<Track*> searchByTitle(const std::string& query) const;

/**
 * @brief Builds the word index from the current content of the library.
 * @return Number of distinct words in the index.
 */
    int rebuildIndex();

/**
 * @brief Returns the indexed library.
 * @return Pointer to the library.
 */
    MediaLibrary* getLibrary() const;
};