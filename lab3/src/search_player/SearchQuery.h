/**
 * @file SearchQuery.h
 * @brief Declaration of the SearchQuery class.
 */
#pragma once
#include <map>
#include <string>

/**
 * @class SearchQuery
 * @brief Text typed by the user together with optional filters.
 *
 * The search service understands the filter "type" with the values "track", "album" or "artist".
 */
class SearchQuery{
protected:
    std::string text;///<Raw text typed by the user.
    std::map<std::string,std::string> filters;///<Filter values by filter name.

public:
/**
 * @brief Constructor with parameters.
 * @param text Raw text typed by the user.
 * @param filters Filter values by filter name.
 */
    explicit SearchQuery(const std::string& text,const std::map<std::string,std::string>& filters=
                         std::map<std::string,std::string>());

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
 * @brief Returns the value of a filter.
 * @param name Name of the filter.
 * @return Value of the filter, empty string if it is not set.
 */
    std::string getFilter(const std::string& name) const;
};