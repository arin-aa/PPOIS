#include "File.h"

File::File():fileName(""),sizeMb(0),isReadOnly(false),content(""){}

File::File(const std::string& fileName,int sizeMb,bool isReadOnly):fileName(fileName),sizeMb(sizeMb),isReadOnly(isReadOnly),content(""){}

bool File::rename(const std::string& newName){
    if(isReadOnly || newName.empty()){
        return false;
    }
    fileName=newName;
    return true;
}

bool File::writeText(const std::string& text){
    if(isReadOnly){
        return false;
    }
    content=text;
    return true;
}

std::string File::getContent(){
    return content;
}

int File::getSizeMb(){
    return sizeMb;
}

std::string File::getFileName(){
    return fileName;
}
