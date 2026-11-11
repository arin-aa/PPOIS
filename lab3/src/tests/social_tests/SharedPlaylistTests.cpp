#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "SharedPlaylist.h"
#include "Playlist.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("SharedPlaylist: Collaborator Management") {
    Playlist playlist(1, "ownerId", "My Playlist", "Desc");
    SharedPlaylist shared(&playlist, "ownerId");

    SECTION("Add valid collaborator") {
        REQUIRE_NOTHROW(shared.addCollaborator("user1"));
    }

    SECTION("Adding owner as collaborator throws PlaylistException") {
        REQUIRE_THROWS_AS(shared.addCollaborator("ownerId"), PlaylistException);
    }

    SECTION("Adding existing collaborator throws PlaylistException") {
        shared.addCollaborator("user1");
        REQUIRE_THROWS_AS(shared.addCollaborator("user1"), PlaylistException);
    }

    SECTION("Remove existing collaborator works") {
        shared.addCollaborator("user1");
        REQUIRE_NOTHROW(shared.removeCollaborator("user1"));
    }

    SECTION("Removing non-existent collaborator throws UserNotFoundException") {
        REQUIRE_THROWS_AS(shared.removeCollaborator("unknown"), UserNotFoundException);
    }
}