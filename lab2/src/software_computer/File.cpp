#include "File.h"
#include "ComputerExceptions.h"

const int CHARS_PER_PAGE=500;

File::File():fileName(""),sizeMb(0),isReadOnly(false),content(""){}

File::File(const std::string& fileName,int sizeMb,bool isReadOnly):fileName(fileName),sizeMb(sizeMb),isReadOnly(isReadOnly),content(""){}

void File::append(const std::string& text){
    if(isReadOnly){
        throw UnauthorizedAccessException(fileName+" is read-only");
    }
    content+=text;
}

int File::pageCount(){
    return static_cast<int>(content.size())/CHARS_PER_PAGE+1;
}

int File::fitInto(int freeMb){
    if(sizeMb>freeMb){
        throw DiskFullException(fileName+" does not fit");
    }
    return freeMb-sizeMb;
}
