#include "RecommendationService.h"
#include "MediaLibrary.h"
#include "MusicPlayerExceptions.h"
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "Track.h"

RecommendationService::RecommendationService(PlaybackHistory* history,MediaLibrary* library):
    history(history),library(library){}

std::vector<Track*> RecommendationService::recommendFor(int count) const{
    std::vector<int> playedGenreIds;
    for(const PlaybackSession& session:history->getSessions()){
        const Track* playedTrack=session.getTrack();
        for(int genreId:playedTrack->getGenreIds()){
            playedGenreIds.push_back(genreId);
        }
    }
    std::vector<Track*> result;
    for(Track* track:library->getTracks()){
        if(static_cast<int>(result.size())>=count){
            break;
        }
        if(track->hasAnyGenre(playedGenreIds)){
            result.push_back(track);
        }
    }
    return result;
}

std::vector<Track*> RecommendationService::similarTracks(int trackId,int count) const{
    const Track* reference=library->findTrackById(trackId);
    if(!reference){
        throw TrackNotFoundException("track "+std::to_string(trackId)+" is not in the library",trackId);
    }
    const std::vector<int>& referenceGenres=reference->getGenreIds();
    std::vector<Track*> result;
    for(Track* candidate:library->getTracks()){
        if(static_cast<int>(result.size())>=count){
            break;
        }
        bool isNotReference=candidate->getId()!=trackId;
        bool sharesGenre=candidate->hasAnyGenre(referenceGenres);
        if(isNotReference && sharesGenre){
            result.push_back(candidate);
        }
    }
    return result;
}