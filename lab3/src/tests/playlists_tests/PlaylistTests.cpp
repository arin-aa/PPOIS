#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Playlist.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"
#include "AudioFile.h"

TEST_CASE("Playlist: Add, Remove and Duration") {
    Playlist playlist(1, "owner", "My Playlist", "desc");
    AudioFile file("a.mp3", "mp3", 320, 100);
    Track t1(1, "Song 1", 1, 1, 1000, &file);
    Track t2(2, "Song 2", 1, 1, 2000, &file);
    Track broken(3, "Broken", 1, 1, 1000, nullptr);

    SECTION("Basic getters") {
        REQUIRE(playlist.getId() == 1);
    }

    SECTION("addTrack throws on invalid track") {
        REQUIRE_THROWS_AS(playlist.addTrack(nullptr), PlaylistException);
        REQUIRE_THROWS_AS(playlist.addTrack(&broken), PlaylistException);
    }

    SECTION("addTrack adds valid track") {
        REQUIRE_NOTHROW(playlist.addTrack(&t1));
        REQUIRE(playlist.getTotalDuration() == 1000);
    }

    SECTION("addTrack throws when playlist is full") {
        for(int i=0; i<1000; ++i) {
            playlist.addTrack(&t1);
        }
        REQUIRE_THROWS_AS(playlist.addTrack(&t1), PlaylistException);
    }

    SECTION("removeTrack updates positions and throws if not found") {
        playlist.addTrack(&t1);
        playlist.addTrack(&t2);
        
        REQUIRE_NOTHROW(playlist.removeTrack(1));
        REQUIRE(playlist.getTotalDuration() == 2000);
        REQUIRE_THROWS_AS(playlist.removeTrack(99), TrackNotFoundException);
    }
}