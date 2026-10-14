#pragma once
#include "Peripheral.h"

class File;

class Printer:public Peripheral{
private:
    int paperLevel;
    int inkLevel;
    int queue;

public:
    Printer();
    Printer(int paperLevel,int inkLevel);

    bool print(File* file);
    void refillPaper(int n);
};