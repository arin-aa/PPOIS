/**
 * @file Artwork.h
 * @brief Declaration of the Artwork class.
 */
#pragma once
#include <string>

/**
 * @class Artwork
 * @brief Cover image of an album or an artist.
 */
class Artwork{
private:
    std::string uri;///<Location of the image.

public:
/**
 * @brief Constructor with a location.
 * @param uri Location of the image.
 */
    explicit Artwork(const std::string& uri);

/**
 * @brief Builds the location of the small version of the image.
 *
 * The suffix "_thumb" is placed before the extension.
 * @return Location of the thumbnail.
 */
    std::string getThumbnailUri() const;
};