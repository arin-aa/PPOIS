#include "Player.h"
#include "AudioEngine.h"
#include "MusicPlayerExceptions.h"
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "PlaybackState.h"
#include "Queue.h"
#include "Track.h"

static void startTrack(AudioEngine* engine,PlaybackState* state,Track* track){
    if(!track->isPlayable()){
        throw PlaybackException("track cannot be played: "+track->getTitle(),0);
    }
    engine->load(track->getAudioFile());
    state->setTrack(track);
    state->updatePosition(0);
    engine->play();
    state->setPlaying(true);
}

static void recordSession(const PlaybackState* state,PlaybackHistory* history,long long now){
    Track* track=state->getCurrentTrack();
    if(!track || state->getPositionMs()<=0){
        return;
    }
    int positionMs=state->getPositionMs();
    long long startedAt=now-positionMs;
    PlaybackSession session(track,startedAt);
    session.finish(now);
    history->add(session);
}

Player::Player(AudioEngine* engine,Queue* queue,PlaybackState* state,PlaybackHistory* history,Equalizer* equalizer):
    engine(engine),queue(queue),state(state),history(history),equalizer(equalizer),volume(engine->getVolume()){}

void Player::play(){
    Track* track=queue->getCurrent();
    if(state->getCurrentTrack()!=track){
        startTrack(engine,state,track);
        return;
    }
    engine->play();
    state->setPlaying(true);
}

void Player::pause(){
    engine->pause();
    state->setPlaying(false);
}

void Player::stop(long long now){
    recordSession(state,history,now);
    engine->pause();
    engine->setPosition(0);
    state->setPlaying(false);
    state->updatePosition(0);
}

void Player::next(long long now){
    Track* following=queue->next();
    recordSession(state,history,now);
    startTrack(engine,state,following);
}

void Player::previous(long long now){
    Track* preceding=queue->previous();
    recordSession(state,history,now);
    startTrack(engine,state,preceding);
}

void Player::seek(int positionMs){
    Track* track=state->getCurrentTrack();
    if(!track){
        throw PlaybackException("no track is loaded",0);
    }
    if(positionMs<0 || positionMs>track->getDurationMs()){
        throw PlaybackException("position is outside the track",positionMs);
    }
    engine->setPosition(positionMs);
    state->updatePosition(positionMs);
}