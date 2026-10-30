#include "NVMe.h"

const char *const NVME_NAME = "NVMe";
const int LANE_MBPS = 900;
const int MAX_QUEUE = 32;

NVMe::NVMe():Storage(NVME_NAME,0),pcieLanes(0),queueDepth(0){}

NVMe::NVMe(int capacityGb,int pcieLanes,int queueDepth)
    :Storage(NVME_NAME,capacityGb),pcieLanes(pcieLanes),
      queueDepth(queueDepth){}

int NVMe::readSpeed(){
  int queue=queueDepth>MAX_QUEUE?MAX_QUEUE:queueDepth;
  return pcieLanes*LANE_MBPS*queue/MAX_QUEUE;
}
