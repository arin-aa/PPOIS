#include "SleepTimer.h"
#include "MusicPlayerExceptions.h"

SleepTimer::SleepTimer():remainingMs(0){}

void SleepTimer::start(int newDurationMs){
    if(newDurationMs<=0){
        throw PlaybackException("sleep timer must be positive",START_POSITION_MS);
    }
    remainingMs=newDurationMs;
}