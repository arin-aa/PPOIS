#include "AudioEngine.h"
#include "AudioFile.h"
#include "MusicPlayerExceptions.h"

const int DEFAULT_VOLUME=50;
const int NO_FILE_ENGINE_CODE=1;
const int CORRUPTED_FILE_ENGINE_CODE=500;

AudioEngine::AudioEngine():currentFile(nullptr),positionMs(0),volume(DEFAULT_VOLUME),playing(false){}

void AudioEngine::load(AudioFile* file){
    if(!file){
        throw AudioEngineException("no audio file to load",NO_FILE_ENGINE_CODE);
    }
    if(file->getBitrate()<=0){
        throw AudioEngineException("file is corrupted: "+file->getUri(),CORRUPTED_FILE_ENGINE_CODE);
    }
    currentFile=file;
    positionMs=0;
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
    positionMs=newPositionMs>0?newPositionMs:0;
}

AudioFile* AudioEngine::getCurrentFile() const{
    return currentFile;
}

int AudioEngine::getVolume() const{
    return volume;
}

bool AudioEngine::getPlaying() const{
    return playing;
}