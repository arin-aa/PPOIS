#pragma once
#include "Storage.h"

class SSD:public Storage{
private:
    int wearPercent;

public:
    SSD();
    explicit SSD(int capacityGb);

    std::string describe() override;
    void trim();
};
