#include "Scanner.h"
#include "File.h"

Scanner::Scanner():Peripheral("Scanner"),resolutionDpi(300),isBusy(false){}

Scanner::Scanner(int resolutionDpi):Peripheral("Scanner"),resolutionDpi(resolutionDpi),isBusy(false){}

File* Scanner::scan(){
    if(isBusy){
        return nullptr;
    }
    isBusy=true;
    File* result=new File("scan.pdf",5,false);
    isBusy=false;
    return result;
}