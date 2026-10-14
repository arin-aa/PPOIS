#pragma once
#include "Storage.h"

class SSD:public Storage{
private:
    int wearPercent;

public:
    SSD();
    SSD(int capacityGb);

    std::string describe() override;
    void trim();
};