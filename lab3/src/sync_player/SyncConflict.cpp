#include "SyncConflict.h"
#include "MusicPlayerExceptions.h"

const std::string LOCAL_STRATEGY="local";
const std::string REMOTE_STRATEGY="remote";
const std::string NEWEST_STRATEGY="newest";

SyncConflict::SyncConflict(const std::string& entityType,long long localVersion,long long remoteVersion):
    entityType(entityType),localVersion(localVersion),remoteVersion(remoteVersion){}

long long SyncConflict::applyResolution(const std::string& strategy) const{
    if(strategy==LOCAL_STRATEGY){
        return localVersion;
    }
    if(strategy==REMOTE_STRATEGY){
        return remoteVersion;
    }
    if(strategy==NEWEST_STRATEGY){
        return localVersion>remoteVersion?localVersion:remoteVersion;
    }
    throw SyncException("unknown conflict strategy: "+strategy,entityType);
}