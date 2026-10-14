#include "File.h"

File::File():fileName(""),sizeMb(0),isReadOnly(false){}

File::File(const std::string& fileName,int sizeMb,bool isReadOnly):fileName(fileName),sizeMb(sizeMb),isReadOnly(isReadOnly){}

bool File::rename(const std::string& newName){
    if(isReadOnly){
        return false;
    }
    if(newName.empty()){
        return false;
    }
    fileName=newName;
    return true;
}