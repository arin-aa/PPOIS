#pragma once
#include <string>

class Folder;

class File{
private:
    std::string fileName;
    int sizeMb;
    bool isReadOnly;

public:
    File();
    File(const std::string& fileName,int sizeMb,bool isReadOnly);

    bool rename(const std::string& newName);

    friend class Folder;
};