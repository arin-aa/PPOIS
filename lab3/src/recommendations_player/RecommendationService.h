/**
 * @file RecommendationService.h
 * @brief Declaration of the RecommendationService class.
 */
#pragma once
#include <string>
#include <vector>

class MediaLibrary;
class PlaybackHistory;
class Track;

/**
 * @class RecommendationService
 * @brief Suggests tracks based on the genres a user listens to.
 */
class RecommendationService{
private:
    PlaybackHistory* history;///<Pointer to the listening history of the user.
    MediaLibrary* library;///<Pointer to the library that provides the candidates.
    std::string userId;///<Identifier of the user who receives recommendations.

public:
/**
 * @brief Constructor with parameters.
 * @param history Pointer to the listening history of the user.
 * @param library Pointer to the library that provides the candidates.
 * @param userId Identifier of the user.
 */
    RecommendationService(PlaybackHistory* history,MediaLibrary* library,const std::string& userId);

/**
 * @brief Recommends tracks that the user has not played yet.
 * @param count Maximum number of tracks.
 * @return Tracks ordered from the best fit to the worst.
 */
    std::vector<Track*> recommendFor(int count) const;

/**
 * @brief Finds tracks that share genres with a track of the library.
 * @param trackId Identifier of the reference track.
 * @param count Maximum number of tracks.
 * @return Tracks ordered by the number of shared genres, the reference track is excluded.
 * @exception TrackNotFoundException if the reference track is not in the library.
 */
    std::vector<Track*> similarTracks(int trackId,int count) const;
};