/**
 * @file SearchQuery.h
 * @brief Declaration of the SearchQuery class.
 */
#pragma once
#include <string>

/**
 * @class SearchQuery
 * @brief Text typed by the user together with optional filters.
 *
 * The type filter can be "track", "album" or "artist", an empty filter means all types.
 */
class SearchQuery{
protected:
    std::string text;///<Raw text typed by the user.
    std::string typeFilter;///<Kind of items to search, empty for all kinds.

public:
/**
 * @brief Constructor with parameters.
 * @param text Raw text typed by the user.
 * @param typeFilter Kind of items to search, empty for all kinds.
 */
    explicit SearchQuery(const std::string& text,const std::string& typeFilter="");

/**
 * @brief Converts the text to a canonical form: lower case words separated by single spaces.
 * @return Normalized text.
 */
    std::string normalize() const;

/**
 * @brief Checks whether the query has no searchable words.
 * @return true if the normalized text is empty.
 */
    bool isEmpty() const;

/**
 * @brief Checks whether items of a kind must be searched.
 * @param itemType Kind of items: "track", "album" or "artist".
 * @return true if the type filter is empty or equal to the kind.
 */
    bool wantsType(const std::string& itemType) const;
};