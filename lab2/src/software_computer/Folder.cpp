#include "Folder.h"
#include "File.h"

Folder::Folder():freeMb(0){}

Folder::Folder(int freeMb):freeMb(freeMb){}

void Folder::addFile(File* file){
    freeMb=file->fitInto(freeMb);
    files.push_back(file);
}

int Folder::totalPages(){
    int pages=0;
    for(File* file:files){
        pages+=file->pageCount();
    }
    return pages;
}
