#include "Printer.h"
#include "File.h"

const char* const PRINTER_NAME="Printer";
const int DEFAULT_INK_LEVEL=100;

Printer::Printer():Peripheral(PRINTER_NAME),paperLevel(0),inkLevel(DEFAULT_INK_LEVEL),queue(0){}

Printer::Printer(int paperLevel,int inkLevel):Peripheral(PRINTER_NAME),paperLevel(paperLevel),inkLevel(inkLevel),queue(0){}

bool Printer::print(File* file){
    if(!file || paperLevel<=0 || inkLevel<=0){
        return false;
    }
    paperLevel--;
    inkLevel--;
    if(queue>0){
        queue--;
    }
    return true;
}

void Printer::refillPaper(int sheetCount){
    if(sheetCount<=0){
        return;
    }
    paperLevel+=sheetCount;
}

int Printer::getPaperLevel(){
    return paperLevel;
}

int Printer::getInkLevel(){
    return inkLevel;
}
