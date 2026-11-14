#include "SyncService.h"
#include "CloudStorage.h"
#include "SyncConflict.h"

SyncService::SyncService(CloudStorage* cloud):cloud(cloud){}

long long SyncService::sync(const std::string& entityType,long long localVersion,const std::string& strategy){
    if(cloud->getLastSyncAt()==NEVER_SYNCED){
        cloud->upload(entityType,localVersion);
        return localVersion;
    }
    long long remoteVersion=cloud->download(entityType);
    SyncConflict conflict(entityType,localVersion,remoteVersion);
    long long resolved=conflict.applyResolution(strategy);
    if(resolved!=remoteVersion){
        cloud->upload(entityType,resolved);
    }
    return resolved;
}