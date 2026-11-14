/**
 * @file MetadataProvider.h
 * @brief Declaration of the MetadataProvider class.
 */
#pragma once
#include <map>
#include <string>

/**
 * @class MetadataProvider
 * @brief Online service that describes audio files.
 */
class MetadataProvider{
private:
    std::string apiUrl;///<Address of the service, empty if the service is not available.

public:
/**
 * @brief Constructor with an address.
 * @param apiUrl Address of the service.
 */
    explicit MetadataProvider(const std::string& apiUrl);

/**
 * @brief Gets the description of an audio file.
 *
 * The title is built from the file name: the extension is cut off and underscores become spaces.
 * @param uri Location of the file.
 * @return Values by key: "title", "format" and "source".
 * @exception MetadataException if the service is not available or the file has no extension.
 */
    std::map<std::string,std::string> fetchMetadata(const std::string& uri) const;
};