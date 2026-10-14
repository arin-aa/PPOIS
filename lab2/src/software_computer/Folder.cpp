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
    for(File* f:files){
        if(f && f->fileName==name){
            return f;
        }
    }
    return nullptr;
}

int Folder::totalSize(){
    int total=0;
    for(File* f:files){
        if(f){
            total+=f->sizeMb;
        }
    }
    for(Folder* sub:subfolders){
        if(sub){
            total+=sub->totalSize();
        }
    }
    return total;
}