#include "Scanner.h"
#include "File.h"

const char* const SCANNER_NAME="Scanner";
const int DEFAULT_SCAN_DPI=300;
const char* const SCAN_FILE_NAME="scan.pdf";
const int SCAN_FILE_SIZE_MB=5;

Scanner::Scanner():Peripheral(SCANNER_NAME),resolutionDpi(DEFAULT_SCAN_DPI),isBusy(false){}

Scanner::Scanner(int resolutionDpi):Peripheral(SCANNER_NAME),resolutionDpi(resolutionDpi),isBusy(false){}

std::unique_ptr<File> Scanner::scan(){
    if(isBusy){
        return nullptr;
    }
    isBusy=true;
    auto scannedFile=std::make_unique<File>(SCAN_FILE_NAME,
                                              SCAN_FILE_SIZE_MB,false);
    isBusy=false;
    return scannedFile;
}
