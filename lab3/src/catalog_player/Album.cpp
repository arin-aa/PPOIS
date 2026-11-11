#include "Album.h"
#include "MediaLibrary.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

Album::Album(int id,const std::string& title,int artistId,const std::vector<int>& trackIds):
    id(id),title(title),artistId(artistId),trackIds(trackIds){}

long long Album::getTotalDuration(const MediaLibrary* library) const{
    long long totalMs=0;
    for(int trackId:trackIds){
        const Track* track=library->findTrackById(trackId);
        if(!track){
            throw TrackNotFoundException("track "+std::to_string(trackId)+" of album "+title+" is not in the library",trackId);
        }
        totalMs+=track->getDurationMs();
    }
    return totalMs;
}

int Album::getTrackCount() const{
    return static_cast<int>(trackIds.size());
}

int Album::getId() const{
    return id;
}

const std::string& Album::getTitle() const{
    return title;
}