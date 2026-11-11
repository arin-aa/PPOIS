#include <catch2/catch_test_macros.hpp>
#include "Artist.h"
#include "Album.h"
#include "MediaLibrary.h"

TEST_CASE("Artist: Getters and Track Count") {
    Album album1(1, "Album 1", 10, {1, 2}); // 2 tracks
    Album album2(2, "Album 2", 10, {3});    // 1 track
    Album album3(3, "Album 3", 10, {4, 5, 6}); // 3 tracks

    MediaLibrary lib({}, {&album1, &album2, &album3});

    SECTION("Basic getters work") {
        Artist artist(10, "The Band", {1, 3}, "url");
        REQUIRE(artist.getName() == "The Band");
    }

    SECTION("hasAlbums returns correct boolean") {
        Artist emptyArtist(10, "Solo", {}, "url");
        Artist activeArtist(11, "Band", {1, 2}, "url");

        REQUIRE(emptyArtist.hasAlbums() == false);
        REQUIRE(activeArtist.hasAlbums() == true);
    }

    SECTION("getTrackCount sums tracks of known albums") {
        // Artist has albums 1 and 3. Library also has album 2, but it should be ignored.
        Artist artist(10, "The Band", {1, 3}, "url");
        
        // Album 1 has 2 tracks, Album 3 has 3 tracks. Total = 5.
        REQUIRE(artist.getTrackCount(&lib) == 5);
    }

    SECTION("getTrackCount returns 0 if no albums match") {
        Artist artist(10, "Unknown", {99, 100}, "url");
        REQUIRE(artist.getTrackCount(&lib) == 0);
    }
}