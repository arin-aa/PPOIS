#include "Scanner.h"

const char* const SCANNER_NAME="Scanner";
const int KB_PER_UNIT=1000;

Scanner::Scanner():Peripheral(SCANNER_NAME),resolutionDpi(0),colorBits(0),pagesScanned(0){}

Scanner::Scanner(int resolutionDpi,int colorBits):Peripheral(SCANNER_NAME),resolutionDpi(resolutionDpi),colorBits(colorBits),pagesScanned(0){}

int Scanner::scanPages(int pages){
    ping();
    pagesScanned+=pages;
    return pages*resolutionDpi*colorBits/KB_PER_UNIT;
}
