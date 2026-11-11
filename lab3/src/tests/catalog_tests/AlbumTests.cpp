#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Album.h"
#include "MediaLibrary.h"
#include "Track.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("Album: Getters and Duration") {
    Album album(1, "Test Album", 10, {1, 2});

    SECTION("Basic getters work") {
        REQUIRE(album.getId() == 1);
        REQUIRE(album.getTitle() == "Test Album");
        REQUIRE(album.getTrackCount() == 2);
    }

    SECTION("getTotalDuration calculates sum correctly") {
        Track t1(1, "Song 1", 10, 1, 1000, nullptr);
        Track t2(2, "Song 2", 10, 1, 2000, nullptr);
        MediaLibrary lib({&t1, &t2});

        REQUIRE(album.getTotalDuration(&lib) == 3000);
    }

    SECTION("getTotalDuration throws if track is missing") {
        Track t1(1, "Song 1", 10, 1, 1000, nullptr);
        MediaLibrary lib({&t1});

        REQUIRE_THROWS_AS(album.getTotalDuration(&lib), TrackNotFoundException);
    }
}