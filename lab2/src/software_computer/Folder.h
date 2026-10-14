#pragma once
#include <string>
#include <vector>

class File;

class Folder{
private:
    std::string folderName;
    std::vector<File*> files;
    std::vector<Folder*> subfolders;

public:
    Folder();
    Folder(const std::string& folderName);

    bool addFile(File* file);
    File* findFile(const std::string& name);
    int totalSize();
};