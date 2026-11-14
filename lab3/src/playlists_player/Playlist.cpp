#include "Playlist.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

const size_t MAX_PLAYLIST_SIZE=1000;

Playlist::Playlist(int id,const std::string& ownerId,const std::string& title,const std::string& description):
    id(id),ownerId(ownerId),title(title),description(description){}

void Playlist::addTrack(Track* track){
    if(!track || !track->isPlayable()){
        throw PlaylistException("track cannot be played",id);
    }
    if(items.size()>=MAX_PLAYLIST_SIZE){
        throw PlaylistException("playlist "+title+" is full",id);
    }
    items.push_back(PlaylistItem(track,static_cast<int>(items.size())));
}

void Playlist::removeTrack(int trackId){
    for(size_t index=0;index<items.size();index++){
        const Track* track=items[index].getTrack();
        if(track->getId()==trackId){
            items.erase(items.begin()+index);
            for(size_t next=index;next<items.size();next++){
                items[next].setPosition(static_cast<int>(next));
            }
            return;
        }
    }
    throw TrackNotFoundException("track "+std::to_string(trackId)+" is not in the playlist "+title,trackId);
}

long long Playlist::getTotalDuration() const{
    long long totalMs=0;
    for(const PlaylistItem& item:items){
        const Track* track=item.getTrack();
        totalMs+=track->getDurationMs();
    }
    return totalMs;
}

int Playlist::getId() const{
    return id;
}