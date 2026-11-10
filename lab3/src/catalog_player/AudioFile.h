/**
 * @file AudioFile.h
 * @brief Declaration of the AudioFile class.
 */
#pragma once
#include <string>

/**
 * @class AudioFile
 * @brief Physical audio file with its encoding parameters.
 */
class AudioFile{
private:
    std::string uri;///<Location of the file.
    std::string format;///<Encoding format without a dot, for example "mp3" or "flac".
    int bitrate;///<Bitrate in kilobits per second.
    long long sizeBytes;///<Size of the file in bytes.

public:
/**
 * @brief Constructor with parameters.
 * @param uri Location of the file.
 * @param format Encoding format.
 * @param bitrate Bitrate in kilobits per second.
 * @param sizeBytes Size of the file in bytes.
 */
    AudioFile(const std::string& uri,const std::string& format,int bitrate,long long sizeBytes);

/**
 * @brief Checks whether the format keeps the sound without loss.
 * @return true for flac, wav and alac.
 */
    bool isLossless() const;

/**
 * @brief Builds the file extension.
 * @return Format with a leading dot.
 */
    std::string getExtension() const;

/**
 * @brief Returns the location of the file.
 * @return File location.
 */
    const std::string& getUri() const;

/**
 * @brief Returns the bitrate.
 * @return Bitrate in kilobits per second.
 */
    int getBitrate() const;

/**
 * @brief Returns the file size.
 * @return Size in bytes.
 */
    long long getSizeBytes() const;
};