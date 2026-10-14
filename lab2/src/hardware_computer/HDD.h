#pragma once
#include "Storage.h"

class HDD:public Storage{
private:
    int rpm;
    int badSectors;

public:
    HDD();
    HDD(int capacityGb,int rpm);

    std::string describe() override;
    void defragment();
};