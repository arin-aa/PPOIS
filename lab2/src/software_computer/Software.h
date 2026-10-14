#pragma once
#include <string>

class Storage;
class OperatingSystem;

class Software{
protected:
    std::string name;
    std::string version;
    int sizeMb;
    bool isInstalled;

public:
    Software();
    Software(const std::string& name,const std::string& version,int sizeMb);
    virtual ~Software()=default;

    virtual bool install(Storage* storage)=0;
    virtual bool uninstall(Storage* storage)=0;

    friend class OperatingSystem;
};