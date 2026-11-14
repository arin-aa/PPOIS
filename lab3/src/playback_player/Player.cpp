#include "Player.h"
#include "AudioEngine.h"
#include "MusicPlayerExceptions.h"
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "PlaybackState.h"
#include "Queue.h"
#include "Track.h"

Player::Player(AudioEngine* engine,Queue* queue,PlaybackState* state,PlaybackHistory* history):
    engine(engine),queue(queue),state(state),history(history){}

void Player::startTrack(Track* track){
    if(!track->isPlayable()){
        throw PlaybackException("track cannot be played: "+track->getTitle(),START_POSITION_MS);
    }
    AudioFile* audioFile=track->getAudioFile();
    engine->load(audioFile);
    state->setTrack(track);
    state->updatePosition(START_POSITION_MS);
    engine->play();
    state->setPlaying(true);
}

void Player::recordSession(long long now){
    Track* track=state->getCurrentTrack();
    if(!track || state->getPositionMs()<=START_POSITION_MS){
        return;
    }
    long long startedAt=now-state->getPositionMs();
    PlaybackSession session(track,startedAt);
    session.finish(now);
    history->add(session);
}

void Player::play(){
    Track* track=queue->getCurrent();
    if(state->getCurrentTrack()!=track){
        startTrack(track);
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
    recordSession(now);
    engine->pause();
    engine->setPosition(START_POSITION_MS);
    state->setPlaying(false);
    state->updatePosition(START_POSITION_MS);
}

void Player::next(long long now){
    Track* following=queue->next();
    recordSession(now);
    startTrack(following);
}

void Player::previous(long long now){
    Track* preceding=queue->previous();
    recordSession(now);
    startTrack(preceding);
}

void Player::seek(int positionMs){
    Track* track=state->getCurrentTrack();
    if(!track){
        throw PlaybackException("no track is loaded",START_POSITION_MS);
    }
    if(positionMs<0 || positionMs>track->getDurationMs()){
        throw PlaybackException("position is outside the track",positionMs);
    }
    engine->setPosition(positionMs);
    state->updatePosition(positionMs);
}