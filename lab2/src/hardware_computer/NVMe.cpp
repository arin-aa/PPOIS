#include "NVMe.h"

NVMe::NVMe():Storage("NVMe",0,3500),pcieLanes(0){}

NVMe::NVMe(int capacityGb,int pcieLanes):Storage("NVMe",capacityGb,3500),pcieLanes(pcieLanes){}

std::string NVMe::describe(){
    return "NVMe "+std::to_string(capacityGb)+"GB";
}

int NVMe::calcThroughput(){
    return pcieLanes*985;
}