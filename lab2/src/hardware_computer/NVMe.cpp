#include "NVMe.h"

const char* const NVME_NAME="NVMe";
const int NVME_READ_SPEED_MB_PER_SEC=3500;
const int LANE_THROUGHPUT_MB_PER_SEC=985;

NVMe::NVMe():Storage(NVME_NAME,0,NVME_READ_SPEED_MB_PER_SEC),pcieLanes(0){}

NVMe::NVMe(int capacityGb,int pcieLanes):Storage(NVME_NAME,capacityGb,NVME_READ_SPEED_MB_PER_SEC),pcieLanes(pcieLanes){}

std::string NVMe::describe(){
    return "NVMe "+std::to_string(capacityGb)+"GB";
}

int NVMe::calcThroughput(){
    return pcieLanes*LANE_THROUGHPUT_MB_PER_SEC;
}
