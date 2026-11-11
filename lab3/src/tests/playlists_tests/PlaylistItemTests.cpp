#include <catch2/catch_test_macros.hpp>
#include "PlaylistItem.h"
#include "Track.h"
#include "AudioFile.h"

TEST_CASE("PlaylistItem: Validity and Getters") {
    AudioFile file("a.mp3", "mp3", 320, 100);
    Track playableTrack(1, "Song", 1, 1, 1000, &file);
    Track brokenTrack(2, "Broken", 1, 1, 1000, nullptr);

    SECTION("Valid item") {
        PlaylistItem item(&playableTrack, 0);
        REQUIRE(item.isValid() == true);
        REQUIRE(item.getTrack() == &playableTrack);
    }

    SECTION("Invalid: null track") {
        PlaylistItem item(nullptr, 0);
        REQUIRE(item.isValid() == false);
    }

    SECTION("Invalid: track not playable") {
        PlaylistItem item(&brokenTrack, 0);
        REQUIRE(item.isValid() == false);
    }

    SECTION("Invalid: negative position") {
        PlaylistItem item(&playableTrack, -1);
        REQUIRE(item.isValid() == false);
    }

    SECTION("setPosition updates position") {
        PlaylistItem item(&playableTrack, -1);
        REQUIRE(item.isValid() == false);
        
        item.setPosition(5);
        REQUIRE(item.isValid() == true);
    }
}