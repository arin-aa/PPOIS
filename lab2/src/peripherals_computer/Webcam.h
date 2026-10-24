#pragma once
#include <memory>
#include <string>
#include "Peripheral.h"

class File;

class Webcam:public Peripheral{
private:
    std::string resolution;
    int fps;
    bool isRecording;

public:
    Webcam();
    Webcam(const std::string& resolution,int fps);

    std::unique_ptr<File> record(int seconds);
};
