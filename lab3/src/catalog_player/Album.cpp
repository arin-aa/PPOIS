#include "Album.h"
#include "MediaLibrary.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

Album::Album(int id,const std::string& title,int artistId,const std::vector<int>& trackIds):
    id(id),title(title),artistId(artistId),trackIds(trackIds){}

long long Album::getTotalDuration(const MediaLibrary* library) const{
    long long totalMs=0;
    for(int trackId:trackIds){
        bool found=false;
        for(const Track* track:library->getTracks()){
            if(track->getId()==trackId){
                totalMs+=track->getDurationMs();
                found=true;
            }
        }
        if(!found){
            throw TrackNotFoundException("track "+std::to_string(trackId)+" of album "+title+" is not in the library",trackId);
        }
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