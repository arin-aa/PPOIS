#include "SharedPlaylist.h"
#include "MusicPlayerExceptions.h"
#include "Playlist.h"

SharedPlaylist::SharedPlaylist(Playlist* playlist,const std::string& ownerId):playlist(playlist),ownerId(ownerId){}

void SharedPlaylist::addCollaborator(const std::string& userId){
    bool canEdit=userId==ownerId;
    for(const std::string& collaboratorId:collaboratorIds){
        if(collaboratorId==userId){
            canEdit=true;
        }
    }
    if(canEdit){
        throw PlaylistException("user already can edit the playlist",playlist->getId());
    }
    collaboratorIds.push_back(userId);
}

void SharedPlaylist::removeCollaborator(const std::string& userId){
    for(size_t index=0;index<collaboratorIds.size();index++){
        if(collaboratorIds[index]==userId){
            collaboratorIds.erase(collaboratorIds.begin()+index);
            return;
        }
    }
    throw UserNotFoundException("user is not a collaborator: "+userId,userId);
}