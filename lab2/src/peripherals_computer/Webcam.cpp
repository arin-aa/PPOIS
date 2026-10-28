#include "Webcam.h"

const char* const WEBCAM_NAME="Webcam";
const int KB_PER_UNIT=10000;

Webcam::Webcam():Peripheral(WEBCAM_NAME),heightPx(0),fps(0),recordedSeconds(0){}

Webcam::Webcam(int heightPx,int fps):Peripheral(WEBCAM_NAME),heightPx(heightPx),fps(fps),recordedSeconds(0){}

int Webcam::record(int seconds){
    ping();
    recordedSeconds+=seconds;
    return seconds*fps*heightPx/KB_PER_UNIT;
}
