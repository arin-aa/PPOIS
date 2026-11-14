#include "AudioEngine.h"
#include "AudioFile.h"
#include "DefaultSettings.h"
#include "MusicPlayerExceptions.h"

const int NO_FILE_ENGINE_CODE=1;

AudioEngine::AudioEngine():currentFile(nullptr),positionMs(0),volume(DEFAULT_VOLUME),playing(false){}

void AudioEngine::load(AudioFile* file){
    if(!file){
        throw AudioEngineException("no audio file to load",NO_FILE_ENGINE_CODE);
    }
    if(file->getBitrate()<=0){
        throw AudioEngineException("file is corrupted: "+file->getUri(),FATAL_ENGINE_CODE);
    }
    currentFile=file;
    positionMs=START_POSITION_MS;
    playing=false;
}

void AudioEngine::play(){
    if(!currentFile){
        throw AudioEngineException("nothing is loaded",NO_FILE_ENGINE_CODE);
    }
    playing=true;
}

void AudioEngine::pause(){
    playing=false;
}

void AudioEngine::setPosition(int newPositionMs){
    positionMs=newPositionMs>0?newPositionMs:START_POSITION_MS;
}