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
 * Tracks are searched through the ContentCatalog (by title),
 * albums and artists are searched by substring of their title or name.
 */
class SearchService{
private:
    ContentCatalog* catalog;///<Pointer to the catalog that is searched.

public:
/**
 * @brief Constructor with a catalog.
 * @param catalog Pointer to the catalog to search in.
 */
    explicit SearchService(ContentCatalog* catalog);

/**
 * @brief Runs a query.
 *
 * The type filter of the query limits the result to tracks, albums or artists.
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