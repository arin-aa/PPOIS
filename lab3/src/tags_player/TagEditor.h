/**
 * @file TagEditor.h
 * @brief Declaration of the TagEditor class.
 */
#pragma once
#include <map>
#include <string>
#include <vector>

/**
 * @class TagEditor
 * @brief Reads and writes descriptive tags of audio files.
 *
 * Tags are kept in the file name in the form "Artist - Title.ext".
 * The format of a file is the extension of its location.
 */
class TagEditor{
protected:
    std::vector<std::string> supportedFormats;///<Formats whose tags can be edited.

/**
 * @brief Takes the format from a location and checks that it is supported.
 * @param uri Location of the file.
 * @return Format of the file, the extension without the dot.
 * @exception MetadataException if the format is not supported.
 */
    std::string extractFormat(const std::string& uri) const;

public:
/**
 * @brief Default constructor. Supported formats are mp3, flac, wav and ogg.
 */
    TagEditor();

/**
 * @brief Reads the tags of a file.
 * @param uri Location of the file, for example "music/Band - Song.mp3".
 * @return Tags "artist" (if present), "title" and "format".
 * @exception MetadataException if the format is not supported.
 */
    std::map<std::string,std::string> readTags(const std::string& uri);

/**
 * @brief Writes tags into the name of a file.
 * @param uri Location of the file.
 * @param tags Tag values, "title" is required and "artist" is optional.
 * @return New location of the file in the form "folder/Artist - Title.ext".
 * @exception MetadataException if the format is not supported or the title is missing.
 */
    std::string writeTags(const std::string& uri,const std::map<std::string,std::string>& tags);
};