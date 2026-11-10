#include "SharedPlaylist.h"
#include <algorithm>
#include "MusicPlayerExceptions.h"
#include "Playlist.h"

SharedPlaylist::SharedPlaylist(Playlist* playlist,const std::string& ownerId):playlist(playlist),ownerId(ownerId){}

void SharedPlaylist::addCollaborator(const std::string& userId){
    bool isCollaborator=std::find(collaboratorIds.begin(),collaboratorIds.end(),userId)!=collaboratorIds.end();
    if(userId==ownerId || isCollaborator){
        throw PlaylistException("user already can edit the playlist",playlist->getId());
    }
    collaboratorIds.push_back(userId);
}

void SharedPlaylist::removeCollaborator(const std::string& userId){
    auto found=std::find(collaboratorIds.begin(),collaboratorIds.end(),userId);
    if(found==collaboratorIds.end()){
        throw UserNotFoundException("user is not a collaborator: "+userId,userId);
    }
    collaboratorIds.erase(found);
}

const std::vector<std::string>& SharedPlaylist::getCollaboratorIds() const{
    return collaboratorIds;
}