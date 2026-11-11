#include <catch2/catch_test_macros.hpp>
#include "Track.h"
#include "AudioFile.h"

TEST_CASE("Track: Playable state and Genres") {
    AudioFile file("a.mp3", "mp3", 320, 100);

    SECTION("isPlayable branch check") {
        Track playable(1, "Song", 1, 1, 1000, &file);
        Track noFile(2, "Song", 1, 1, 1000, nullptr);
        Track zeroDuration(3, "Song", 1, 1, 0, &file);

        REQUIRE(playable.isPlayable() == true);
        REQUIRE(noFile.isPlayable() == false);
        REQUIRE(zeroDuration.isPlayable() == false);
    }

    SECTION("hasGenre and hasAnyGenre work correctly") {
        Track t(1, "Song", 1, 1, 1000, nullptr, {1, 2});
        
        REQUIRE(t.hasGenre(1) == true);
        REQUIRE(t.hasGenre(3) == false);

        REQUIRE(t.hasAnyGenre({3, 4}) == false);
        REQUIRE(t.hasAnyGenre({3, 2}) == true);
        REQUIRE(t.hasAnyGenre({}) == false); // empty list
    }

    SECTION("matchesQuery handles empty query") {
        Track t(1, "Song", 1, 1, 1000, nullptr);
        REQUIRE(t.matchesQuery("") == false);
        REQUIRE(t.matchesQuery("   ") == false);
    }

    SECTION("Getters return correct values") {
        Track t(1, "Song", 2, 3, 1000, &file, {1});
        REQUIRE(t.getId() == 1);
        REQUIRE(t.getTitle() == "Song");
        REQUIRE(t.getArtistId() == 2);
        REQUIRE(t.getDurationMs() == 1000);
        REQUIRE(t.getAudioFile() == &file);
        REQUIRE(t.getGenreIds().size() == 1);
    }
}