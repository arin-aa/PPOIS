#include "PlaybackState.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

PlaybackState::PlaybackState():currentTrack(nullptr),positionMs(START_POSITION_MS),playing(false),shuffle(false){}

int PlaybackState::updatePosition(int newPositionMs){
    if(newPositionMs<0){
        throw PlaybackException("position cannot be negative",newPositionMs);
    }
    positionMs=newPositionMs;
    if(currentTrack && positionMs>currentTrack->getDurationMs()){
        positionMs=currentTrack->getDurationMs();
    }
    return positionMs;
}

bool PlaybackState::toggleShuffle(){
    shuffle=!shuffle;
    return shuffle;
}

void PlaybackState::setTrack(Track* track){
    currentTrack=track;
}

void PlaybackState::setPlaying(bool isPlaying){
    playing=isPlaying;
}

Track* PlaybackState::getCurrentTrack() const{
    return currentTrack;
}

int PlaybackState::getPositionMs() const{
    return positionMs;
}