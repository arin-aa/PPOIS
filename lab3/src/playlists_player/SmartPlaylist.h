/**
 * @file SmartPlaylist.h
 * @brief Declaration of the SmartPlaylist class.
 */
#pragma once
#include <string>
#include <vector>

class MediaLibrary;
class Track;

/**
 * @class SmartPlaylist
 * @brief Playlist built automatically from rules.
 *
 * A rule has the form "key:value". Supported keys are genre, artist (identifiers),
 * minDuration, maxDuration (milliseconds) and title (text that the title must contain).
 */
class SmartPlaylist{
private:
    std::string name;///<Name of the playlist.
    std::vector<std::string> rules;///<Rules that every track must satisfy.

public:
/**
 * @brief Constructor with parameters.
 * @param name Name of the playlist.
 * @param rules Rules in the form "key:value".
 */
    SmartPlaylist(const std::string& name,const std::vector<std::string>& rules);

/**
 * @brief Selects the tracks of a library that satisfy all rules.
 * @param library Pointer to the library to choose from.
 * @return Matching tracks.
 */
    std::vector<Track*> evaluate(const MediaLibrary* library) const;

/**
 * @brief Checks one track against one rule.
 * @param track Track to check.
 * @param rule Rule in the form "key:value".
 * @return true if the track satisfies the rule, false if it does not or the rule is malformed.
 */
    bool matchesRule(const Track* track,const std::string& rule) const;
};