#pragma once
#include "Storage.h"

class HDD:public Storage{
private:
    int rpm;
    int badSectors;
    int fragmentationPercent;

public:
    HDD();
    HDD(int capacityGb,int rpm);

    std::string describe() override;
    bool defragment();
};
