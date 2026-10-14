#pragma once
#include "Storage.h"

class NVMe:public Storage{
private:
    int pcieLanes;

public:
    NVMe();
    NVMe(int capacityGb,int pcieLanes);

    std::string describe() override;
    int calcThroughput();
};