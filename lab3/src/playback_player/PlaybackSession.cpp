#include "PlaybackSession.h"
#include <algorithm>
#include "Track.h"

const int COMPLETION_PERCENT=90;
const int PERCENT_BASE=100;

PlaybackSession::PlaybackSession(Track* track,long long startedAt):track(track),startedAt(startedAt),listenedMs(0){}

int PlaybackSession::finish(long long endedAt){
    long long elapsedMs=std::max(0LL,endedAt-startedAt);

    long long durationMs=static_cast<long long>(track->getDurationMs());
    long long cappedMs=std::min(elapsedMs,durationMs);

    listenedMs=static_cast<int>(cappedMs);
    return listenedMs;
}

bool PlaybackSession::isCompleted() const{
    long long durationMs=static_cast<long long>(track->getDurationMs());
    long long requiredMs=durationMs*COMPLETION_PERCENT/PERCENT_BASE;
    return listenedMs>=requiredMs;
}

Track* PlaybackSession::getTrack() const{
    return track;
}

int PlaybackSession::getListenedMs() const{
    return listenedMs;
}