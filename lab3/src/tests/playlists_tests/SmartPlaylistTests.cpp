#include <catch2/catch_test_macros.hpp>
#include "SmartPlaylist.h"
#include "MediaLibrary.h"
#include "Track.h"

TEST_CASE("SmartPlaylist: Rule Evaluation") {
    Track t1(1, "Rock Song", 1, 1, 1000, nullptr, {1});
    Track t2(2, "Pop Song", 2, 2, 2000, nullptr, {2});
    Track t3(3, "Rock Ballad", 1, 3, 3000, nullptr, {1});
    
    MediaLibrary lib({&t1, &t2, &t3});

    SECTION("Empty rules selects all tracks") {
        SmartPlaylist playlist("All", {});
        REQUIRE(playlist.evaluate(&lib).size() == 3);
    }

    SECTION("Filter by title") {
        SmartPlaylist playlist("Rock", {"title:rock"});
        auto res = playlist.evaluate(&lib);
        REQUIRE(res.size() == 2); 
    }

    SECTION("Filter by genre") {
        SmartPlaylist playlist("Rock Genre", {"genre:1"});
        auto res = playlist.evaluate(&lib);
        REQUIRE(res.size() == 2); 
    }

    SECTION("Filter by artist") {
        SmartPlaylist playlist("Artist 1", {"artist:1"});
        auto res = playlist.evaluate(&lib);
        REQUIRE(res.size() == 2); 
    }

    SECTION("Filter by duration (min/max)") {
        SmartPlaylist playlist("Long", {"minDuration:2000"});
        REQUIRE(playlist.evaluate(&lib).size() == 2); 
        
        SmartPlaylist playlistShort("Short", {"maxDuration:1000"});
        REQUIRE(playlistShort.evaluate(&lib).size() == 1); 
    }

    SECTION("Multiple rules use AND logic") {
        SmartPlaylist playlist("Rock and Short", {"genre:1", "maxDuration:1000"});
        auto res = playlist.evaluate(&lib);
        REQUIRE(res.size() == 1); 
    }

    SECTION("Invalid rules are ignored") {
        SmartPlaylist noSeparator("Bad", {"justtext"});
        REQUIRE(noSeparator.evaluate(&lib).empty());

        SmartPlaylist badNumber("Bad Number", {"genre:abc"});
        REQUIRE(badNumber.evaluate(&lib).empty());
    }
}