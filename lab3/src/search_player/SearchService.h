/**
 * @file SearchService.h
 * @brief Declaration of the SearchService class.
 */
#pragma once
#include <string>
#include <vector>
#include "SearchResult.h"

class ContentCatalog;
class SearchQuery;

/**
 * @class SearchService
 * @brief Searches tracks, albums and artists of a catalog.
 *
 * Tracks are searched through the ContentCatalog (by title words),
 * albums and artists are searched by substring of their title or name.
 */
class SearchService{
private:
    ContentCatalog* catalog;///<Pointer to the catalog that is searched.
    std::string lastQuery;///<Normalized text of the last successful search.

/**
 * @brief Finds albums whose title contains a text.
 * @param text Normalized text to look for.
 * @return Albums that contain the text, in library order.
 */
    std::vector<Album*> searchAlbums(const std::string& text) const;

/**
 * @brief Finds artists whose name contains a text.
 * @param text Normalized text to look for.
 * @return Artists that contain the text, in library order.
 */
    std::vector<Artist*> searchArtists(const std::string& text) const;

public:
/**
 * @brief Constructor with a catalog.
 * @param catalog Pointer to the catalog to search in.
 */
    explicit SearchService(ContentCatalog* catalog);

/**
 * @brief Runs a query.
 *
 * The filter "type" limits the result to tracks, albums or artists.
 * An empty filter searches all three collections.
 * @param query Query to run.
 * @return Found items, empty if the query has no words.
 */
    SearchResult search(const SearchQuery& query);

/**
 * @brief Proposes track titles that start with a text.
 *
 * The comparison is case-sensitive: "Hel" matches "Hello" but "hel" does not.
 * @param prefix Beginning of a title.
 * @return Up to five titles.
 */
    std::vector<std::string> suggest(const std::string& prefix) const;
};