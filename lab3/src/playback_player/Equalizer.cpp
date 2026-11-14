#include "Equalizer.h"
#include "MusicPlayerExceptions.h"

const int BAND_COUNT=10;
const int NO_GAIN=0;
const int MIN_GAIN=-12;
const int MAX_GAIN=12;
const int EQUALIZER_ERROR_CODE=2;
const std::string FLAT_PRESET="flat";
const std::string BASS_PRESET="bass";
const std::string TREBLE_PRESET="treble";
const std::vector<int> FLAT_GAINS(BAND_COUNT,NO_GAIN);
const std::vector<int> BASS_GAINS={6,5,4,2,0,0,0,0,0,0};
const std::vector<int> TREBLE_GAINS={0,0,0,0,0,1,2,4,5,6};

Equalizer::Equalizer():bands(FLAT_GAINS){}

void Equalizer::applyPreset(const std::string& presetName){
    if(presetName==FLAT_PRESET){
        bands=FLAT_GAINS;
    }else if(presetName==BASS_PRESET){
        bands=BASS_GAINS;
    }else if(presetName==TREBLE_PRESET){
        bands=TREBLE_GAINS;
    }else{
        throw AudioEngineException("unknown equalizer preset: "+presetName,EQUALIZER_ERROR_CODE);
    }
}

void Equalizer::setBandGain(int bandIndex,int gain){
    bool isBandWrong=bandIndex<0 || bandIndex>=BAND_COUNT;
    bool isGainWrong=gain<MIN_GAIN || gain>MAX_GAIN;
    if(isBandWrong || isGainWrong){
        throw AudioEngineException("invalid equalizer band or gain",EQUALIZER_ERROR_CODE);
    }
    bands[static_cast<size_t>(bandIndex)]=gain;
}