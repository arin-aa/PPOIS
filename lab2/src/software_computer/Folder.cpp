#include "Folder.h"
#include "File.h"

Folder::Folder():folderName(""){}

Folder::Folder(const std::string& folderName):folderName(folderName){}

bool Folder::addFile(File* file){
    if(!file){
        return false;
    }
    files.push_back(file);
    return true;
}

File* Folder::findFile(const std::string& name){
    for(File* file:files){
        if(file && file->fileName==name){
            return file;
        }
    }
    return nullptr;
}

int Folder::totalSize(){
    int totalMb=0;
    for(File* file:files){
        if(file){
            totalMb+=file->sizeMb;
        }
    }
    for(Folder* subfolder:subfolders){
        if(subfolder){
            totalMb+=subfolder->totalSize();
        }
    }
    return totalMb;
}
