#pragma once
#include "Peripheral.h"
#include <string>

class File;

class Webcam:public Peripheral{
private:
    std::string resolution;
    int fps;
    bool isRecording;

public:
    Webcam();
    Webcam(const std::string& resolution,int fps);

    File* record(int seconds);
};