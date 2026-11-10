#include "Device.h"

const long long ONLINE_TIMEOUT_MS=300000;

Device::Device(const std::string& id,const std::string& name,const std::string& platform,long long lastActiveAt,
               const std::string& syncToken):
    id(id),name(name),platform(platform),lastActiveAt(lastActiveAt),syncToken(syncToken){}

void Device::touch(long long now){
    lastActiveAt=now;
}

bool Device::isOnline(long long now) const{
    return now-lastActiveAt<=ONLINE_TIMEOUT_MS;
}