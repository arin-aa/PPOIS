#include "PlaybackSession.h"
#include "Track.h"

const int COMPLETION_PERCENT=90;
const int PERCENT_BASE=100;

PlaybackSession::PlaybackSession(Track* track,long long startedAt):track(track),startedAt(startedAt),listenedMs(0){}

int PlaybackSession::finish(long long endedAt){
    long long elapsedMs=endedAt-startedAt;
    long long durationMs=track->getDurationMs();
    if(elapsedMs<0){
        elapsedMs=0;
    }
    if(elapsedMs>durationMs){
        elapsedMs=durationMs;
    }
    listenedMs=static_cast<int>(elapsedMs);
    return listenedMs;
}

bool PlaybackSession::isCompleted() const{
    long long durationMs=track->getDurationMs();
    long long requiredMs=durationMs*COMPLETION_PERCENT/PERCENT_BASE;
    return listenedMs>=requiredMs;
}

Track* PlaybackSession::getTrack() const{
    return track;
}