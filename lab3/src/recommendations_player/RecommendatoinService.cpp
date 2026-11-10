#include "RecommendationService.h"
#include <algorithm>
#include <map>
#include "MediaLibrary.h"
#include "MusicPlayerExceptions.h"
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "Track.h"

typedef std::map<int,int> GenreScores;

static int scoreTrack(const Track* track,const GenreScores& genreScores){
    int score=0;
    for(int genreId:track->getGenreIds()){
        auto found=genreScores.find(genreId);
        score+=found==genreScores.end()?0:found->second;
    }
    return score;
}

RecommendationService::RecommendationService(PlaybackHistory* history,MediaLibrary* library,const std::string& userId):
    history(history),library(library),userId(userId){}

std::vector<Track*> RecommendationService::recommendFor(int count) const{
    GenreScores genreScores;
    for(const PlaybackSession& session:history->getSessions()){
        const Track* track=session.getTrack();
        for(int genreId:track->getGenreIds()){
            genreScores[genreId]++;
        }
    }
    std::vector<Track*> result;
    for(Track* track:library->getTracks()){
        if(static_cast<int>(result.size())>=count) break;
        if(scoreTrack(track,genreScores)>0){
            result.push_back(track);
        }
    }
    return result;
}

std::vector<Track*> RecommendationService::similarTracks(int trackId,int count) const{
    const Track* reference=nullptr;
    for(const Track* track:library->getTracks()){
        if(track->getId()==trackId){
            reference=track;
            break;
        }
    }
    if(!reference){
        throw TrackNotFoundException("track "+std::to_string(trackId)+" is not in the library",trackId);
    }
    GenreScores referenceGenres;
    for(int genreId:reference->getGenreIds()){
        referenceGenres[genreId]=1;
    }
    std::vector<Track*> result;
    for(Track* candidate:library->getTracks()){
        if(static_cast<int>(result.size())>=count) break;
        if(candidate->getId()!=trackId && scoreTrack(candidate,referenceGenres)>0){
            result.push_back(candidate);
        }
    }
    return result;
}