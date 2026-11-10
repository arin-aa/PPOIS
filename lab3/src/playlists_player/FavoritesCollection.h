/**
 * @file FavoritesCollection.h
 * @brief Declaration of the FavoritesCollection class.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class FavoritesCollection
 * @brief Tracks that a user marked as favorite.
 */
class FavoritesCollection{
private:
    std::string userId;///<Identifier of the owner.
    std::vector<int> trackIds;///<Identifiers of favorite tracks.
    long long updatedAt;///<Moment of the last change (ms).

public:
/**
 * @brief Constructor that creates an empty collection.
 * @param userId Identifier of the owner.
 */
    explicit FavoritesCollection(const std::string& userId);

/**
 * @brief Adds a track to favorites or removes it if it is already there.
 * @param trackId Identifier of the track.
 * @param now Current time (ms).
 * @return true if the track became a favorite, false if it was removed.
 */
    bool toggle(int trackId,long long now);

/**
 * @brief Checks whether a track is a favorite.
 * @param trackId Identifier of the track.
 * @return true if the track is in the collection.
 */
    bool contains(int trackId) const;
};