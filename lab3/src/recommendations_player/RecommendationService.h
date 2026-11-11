/**
 * @file RecommendationService.h
 * @brief Declaration of the RecommendationService class.
 */
#pragma once
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

public:
/**
 * @brief Constructor with parameters.
 * @param history Pointer to the listening history of the user.
 * @param library Pointer to the library that provides the candidates.
 */
    RecommendationService(PlaybackHistory* history,MediaLibrary* library);

/**
 * @brief Recommends tracks that have a genre of the tracks the user has played.
 * @param count Maximum number of tracks.
 * @return Matching tracks in the order of the library.
 */
    std::vector<Track*> recommendFor(int count) const;

/**
 * @brief Finds tracks that share genres with a track of the library.
 * @param trackId Identifier of the reference track.
 * @param count Maximum number of tracks.
 * @return Tracks that share a genre in the order of the library, the reference track is excluded.
 * @exception TrackNotFoundException if the reference track is not in the library.
 */
    std::vector<Track*> similarTracks(int trackId,int count) const;
};