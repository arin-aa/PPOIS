#include "CloudStorage.h"
#include "MusicPlayerExceptions.h"

CloudStorage::CloudStorage(const std::string& apiUrl,const std::string& token):apiUrl(apiUrl),token(token),lastSyncAt(0){}

long long CloudStorage::download(const std::string& entityType) const{
    if(token.empty()){
        throw SyncException("not authorized for "+apiUrl,entityType);
    }
    if(lastSyncAt==0){
        throw SyncException("nothing is stored for "+entityType,entityType);
    }
    return lastSyncAt;
}

void CloudStorage::upload(const std::string& entityType,long long version){
    if(token.empty()){
        throw SyncException("not authorized for "+apiUrl,entityType);
    }
    lastSyncAt=version;
}

long long CloudStorage::getLastSyncAt() const{
    return lastSyncAt;
}