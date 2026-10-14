#pragma once
#include "Peripheral.h"

class File;

class Scanner:public Peripheral{
private:
    int resolutionDpi;
    bool isBusy;

public:
    Scanner();
    Scanner(int resolutionDpi);

    File* scan();
};