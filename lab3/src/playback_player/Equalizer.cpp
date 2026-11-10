#include "Equalizer.h"
#include <map>
#include "MusicPlayerExceptions.h"

const size_t BAND_COUNT=10;
const int MIN_GAIN=-12;
const int MAX_GAIN=12;
const int EQUALIZER_ERROR_CODE=2;

Equalizer::Equalizer():bands(BAND_COUNT,0),enabled(false){}

void Equalizer::applyPreset(const std::string& presetName){
    if(presetName=="flat"){
        bands={0,0,0,0,0,0,0,0,0,0};
    }else if(presetName=="bass"){
        bands={6,5,4,2,0,0,0,0,0,0};
    }else if(presetName=="treble"){
        bands={0,0,0,0,0,1,2,4,5,6};
    }else{
        throw AudioEngineException("unknown equalizer preset: "+presetName,EQUALIZER_ERROR_CODE);
    }
    enabled=true;
}

void Equalizer::setBandGain(int bandIndex,int gain){
    if(bandIndex<0 || static_cast<size_t>(bandIndex)>=BAND_COUNT || gain<MIN_GAIN || gain>MAX_GAIN){
        throw AudioEngineException("invalid equalizer band or gain",EQUALIZER_ERROR_CODE);
    }
    bands[static_cast<size_t>(bandIndex)]=gain;
}

int Equalizer::getGain(int bandIndex) const{
    if(bandIndex<0 || static_cast<size_t>(bandIndex)>=BAND_COUNT){
        return 0;
    }
    return bands[static_cast<size_t>(bandIndex)];
}