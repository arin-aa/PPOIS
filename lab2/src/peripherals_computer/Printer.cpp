#include "Printer.h"
#include "File.h"

Printer::Printer():Peripheral("Printer"),paperLevel(0),inkLevel(100),queue(0){}

Printer::Printer(int paperLevel,int inkLevel):Peripheral("Printer"),paperLevel(paperLevel),inkLevel(inkLevel),queue(0){}

bool Printer::print(File* file){
    if(!file){
        return false;
    }
    if(paperLevel<=0 || inkLevel<=0){
        return false;
    }
    paperLevel--;
    inkLevel--;
    return true;
}

void Printer::refillPaper(int n){
    if(n<=0){
        return;
    }
    paperLevel+=n;
}