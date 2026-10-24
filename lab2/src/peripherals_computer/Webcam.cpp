#include "Webcam.h"
#include "File.h"

const char* const WEBCAM_NAME="Webcam";
const char* const VIDEO_FILE_NAME="video.mp4";
const int SECONDS_PER_MEGABYTE=10;

Webcam::Webcam():Peripheral(WEBCAM_NAME),resolution(""),fps(0),isRecording(false){}

Webcam::Webcam(const std::string& resolution,int fps):Peripheral(WEBCAM_NAME),resolution(resolution),fps(fps),isRecording(false){}

std::unique_ptr<File> Webcam::record(int seconds){
    if(seconds<=0){
        return nullptr;
    }
    isRecording=true;
    int sizeMb=seconds/SECONDS_PER_MEGABYTE+1;
    auto video=std::make_unique<File>(VIDEO_FILE_NAME,sizeMb,false);
    isRecording=false;
    return video;
}
