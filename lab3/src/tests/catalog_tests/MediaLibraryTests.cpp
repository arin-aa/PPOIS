#include <catch2/catch_test_macros.hpp>
#include "MediaLibrary.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"

TEST_CASE("MediaLibrary: Add and Find Tracks") {
    MediaLibrary lib;
    Track t1(1, "Rock Song", 1, 1, 1000, nullptr, {1}); 
    Track t2(2, "Pop Song", 2, 2, 1000, nullptr, {2});  

    SECTION("addTrack checks for duplicates") {
        REQUIRE(lib.addTrack(&t1) == true);
        REQUIRE(lib.addTrack(&t1) == false); 
        REQUIRE(lib.getTracks().size() == 1);
    }

    SECTION("findTrackById returns pointer or nullptr") {
        lib.addTrack(&t1);
        REQUIRE(lib.findTrackById(1) == &t1);
        REQUIRE(lib.findTrackById(99) == nullptr);
    }

    SECTION("findByGenre filters correctly") {
        lib.addTrack(&t1);
        lib.addTrack(&t2);
        auto res = lib.findByGenre(1);
        REQUIRE(res.size() == 1);
        REQUIRE(res[0] == &t1);
        
        REQUIRE(lib.findByGenre(99).empty() == true);
    }

    SECTION("findByTitle uses Track::matchesQuery") {
        lib.addTrack(&t1);
        lib.addTrack(&t2);
        auto res = lib.findByTitle("rock");
        REQUIRE(res.size() == 1);
        REQUIRE(res[0] == &t1);
    }
}

TEST_CASE("MediaLibrary: Find Albums and Artists") {
    MediaLibrary lib;
    Album a1(1, "Great Album", 1, {});
    Artist ar1(1, "Great Artist", {}, "");
    
    lib = MediaLibrary({}, {&a1}, {&ar1});

    SECTION("findAlbumsByTitle filters correctly") {
        auto res = lib.findAlbumsByTitle("Great");
        REQUIRE(res.size() == 1);
        REQUIRE(res[0] == &a1);

        REQUIRE(lib.findAlbumsByTitle("bad").empty() == true);
    }

    SECTION("findArtistsByName filters correctly") {
        auto res = lib.findArtistsByName("Great");
        REQUIRE(res.size() == 1);
        REQUIRE(res[0] == &ar1);

        REQUIRE(lib.findArtistsByName("bad").empty() == true);
    }
}