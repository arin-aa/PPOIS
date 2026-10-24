#pragma once
#include <string>

class Folder;

class File{
private:
    std::string fileName;
    int sizeMb;
    bool isReadOnly;
    std::string content;

public:
    File();
    File(const std::string& fileName,int sizeMb,bool isReadOnly);

    bool rename(const std::string& newName);
    bool writeText(const std::string& text);
    std::string getContent();
    int getSizeMb();
    std::string getFileName();

    friend class Folder;
};
