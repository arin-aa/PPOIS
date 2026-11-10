#include "SleepTimer.h"
#include "MusicPlayerExceptions.h"

SleepTimer::SleepTimer():durationMs(0),remainingMs(0){}

void SleepTimer::start(int newDurationMs){
    if(newDurationMs<=0){
        throw PlaybackException("sleep timer must be positive",0);
    }
    durationMs=newDurationMs;
    remainingMs=newDurationMs;
}

int SleepTimer::getRemainingMs() const{
    return remainingMs;
}