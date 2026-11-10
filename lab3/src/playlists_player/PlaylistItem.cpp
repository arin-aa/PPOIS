#include "PlaylistItem.h"
#include "Track.h"

PlaylistItem::PlaylistItem(Track* track,int position):track(track),position(position){}

bool PlaylistItem::isValid() const{
    return track!=nullptr && track->isPlayable() && position>=0;
}

void PlaylistItem::setPosition(int newPosition){
    position=newPosition;
}

Track* PlaylistItem::getTrack() const{
    return track;
}

int PlaylistItem::getPosition() const{
    return position;
}