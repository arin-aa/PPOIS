#include "Playlist.h"
#include <algorithm>
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
    auto matchesId=[trackId](const PlaylistItem& item){
        const Track* track=item.getTrack();
        int id=track->getId();
        return id==trackId;
    };
    auto found=std::find_if(items.begin(),items.end(),matchesId);
    if(found==items.end()){
        throw TrackNotFoundException("track "+std::to_string(trackId)+" is not in the playlist "+title,trackId);
    }
    items.erase(found);
    for(size_t index=0;index<items.size();index++){
        items[index].setPosition(static_cast<int>(index));
    }
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

const std::string& Playlist::getOwnerId() const{
    return ownerId;
}

const std::string& Playlist::getTitle() const{
    return title;
}

const std::vector<PlaylistItem>& Playlist::getItems() const{
    return items;
}