#pragma once
#include "Component.h"

class Cooler:public Component{
protected:
    int maxTdpWatts;
    int noiseDb;

public:
    Cooler();
    Cooler(const std::string& name,int maxTdpWatts,int noiseDb);

    bool canCool(int tdp);
};