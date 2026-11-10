/**
 * @file Genre.h
 * @brief Declaration of the Genre class.
 */
#pragma once
#include <string>

/**
 * @class Genre
 * @brief Music genre. Subgenres are written as "parent/child".
 */
class Genre{
private:
    int id;///<Unique identifier of the genre.
    std::string name;///<Name of the genre, for example "rock/punk".

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param name Name of the genre.
 */
    Genre(int id,const std::string& name);

/**
 * @brief Checks whether this genre is a subgenre of another one.
 * @param parent Possible parent genre.
 * @return true if the name starts with the parent name followed by "/".
 */
    bool isSubgenreOf(const Genre& parent) const;

/**
 * @brief Returns the identifier.
 * @return Genre identifier.
 */
    int getId() const;

/**
 * @brief Returns the name.
 * @return Genre name.
 */
    const std::string& getName() const;
};