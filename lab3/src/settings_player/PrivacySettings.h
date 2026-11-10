/**
 * @file PrivacySettings.h
 * @brief Declaration of the PrivacySettings class.
 */
#pragma once

/**
 * @class PrivacySettings
 * @brief Choice of what other users may see.
 */
class PrivacySettings{
private:
    bool shareListening;///<Whether listening activity is visible to followers.
    bool publicPlaylists;///<Whether playlists are visible to everybody.

public:
/**
 * @brief Constructor with parameters.
 * @param shareListening Whether listening activity is visible to followers.
 * @param publicPlaylists Whether playlists are visible to everybody.
 */
    PrivacySettings(bool shareListening,bool publicPlaylists);

/**
 * @brief Checks whether nothing is shared.
 * @return true if both options are off.
 */
    bool isPrivate() const;
};