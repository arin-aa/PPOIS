/**
 * @file SharedPlaylist.h
 * @brief Declaration of the SharedPlaylist class.
 */
#pragma once
#include <string>
#include <vector>

class Playlist;

/**
 * @class SharedPlaylist
 * @brief Playlist that several users can edit.
 */
class SharedPlaylist{
private:
    Playlist* playlist;///<Pointer to the playlist that is shared.
    std::string ownerId;///<Identifier of the owner.
    std::vector<std::string> collaboratorIds;///<Identifiers of users who may edit the playlist.

public:
/**
 * @brief Constructor that creates a playlist without collaborators.
 * @param playlist Pointer to the playlist to share.
 * @param ownerId Identifier of the owner.
 */
    SharedPlaylist(Playlist* playlist,const std::string& ownerId);

/**
 * @brief Allows a user to edit the playlist.
 * @param userId Identifier of the user.
 * @exception PlaylistException if the user is the owner or is already a collaborator.
 */
    void addCollaborator(const std::string& userId);

/**
 * @brief Takes the editing right away from a user.
 * @param userId Identifier of the user.
 * @exception UserNotFoundException if the user is not a collaborator.
 */
    void removeCollaborator(const std::string& userId);

/**
 * @brief Returns the identifiers of the collaborators.
 * @return Identifiers without the owner.
 */
    const std::vector<std::string>& getCollaboratorIds() const;
};