#pragma once
#include <memory>
#include "Peripheral.h"

class File;

class Scanner:public Peripheral{
private:
    int resolutionDpi;
    bool isBusy;

public:
    Scanner();
    explicit Scanner(int resolutionDpi);

    std::unique_ptr<File> scan();
};
