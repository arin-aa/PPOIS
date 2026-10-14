#include "Webcam.h"
#include "File.h"

Webcam::Webcam():Peripheral("Webcam"),resolution(""),fps(0),isRecording(false){}

Webcam::Webcam(const std::string& resolution,int fps):Peripheral("Webcam"),resolution(resolution),fps(fps),isRecording(false){}

File* Webcam::record(int seconds){
    if(seconds<=0){
        return nullptr;
    }
    isRecording=true;
    File* result=new File("video.mp4",seconds/10+1,false);
    isRecording=false;
    return result;
}