#include "Printer.h"
#include "ComputerExceptions.h"
#include "File.h"

const char* const PRINTER_NAME="Printer";
const int MAX_PAPER=250;
const int INK_PER_PAGE=1;

Printer::Printer():Peripheral(PRINTER_NAME),paperLevel(0),inkLevel(0),printedPages(0){}

Printer::Printer(int paperLevel,int inkLevel):Peripheral(PRINTER_NAME),paperLevel(paperLevel),inkLevel(inkLevel),printedPages(0){}

int Printer::print(File* file){
    ping();
    int pages=file->pageCount();
    if(pages>paperLevel || pages*INK_PER_PAGE>inkLevel){
        throw PeripheralNotRespondingException("printer is out of paper or ink");
    }
    paperLevel-=pages;
    inkLevel-=pages*INK_PER_PAGE;
    printedPages+=pages;
    return printedPages;
}

int Printer::loadPaper(int sheets){
    paperLevel+=sheets;
    if(paperLevel>MAX_PAPER){
        paperLevel=MAX_PAPER;
    }
    return paperLevel;
}
