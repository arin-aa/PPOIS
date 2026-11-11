#include <catch2/catch_test_macros.hpp>
#include "PlaybackSession.h"
#include "Track.h"

TEST_CASE("PlaybackSession: Finish and Completion") {
    Track track(1, "Song", 1, 1, 1000, nullptr);
    PlaybackSession session(&track, 0);

    SECTION("Finish clamps negative time to 0") {
        REQUIRE(session.finish(-500) == 0);
        REQUIRE(session.isCompleted() == false);
    }

    SECTION("Finish clamps time exceeding duration to duration") {
        REQUIRE(session.finish(5000) == 1000);
        REQUIRE(session.isCompleted() == true);
    }

    SECTION("Finish normal time calculates completion correctly") {
        PlaybackSession s1(&track, 0);
        s1.finish(890);
        REQUIRE(s1.isCompleted() == false);

        PlaybackSession s2(&track, 0);
        s2.finish(900);
        REQUIRE(s2.isCompleted() == true);
    }

    SECTION("getTrack returns correct pointer") {
        REQUIRE(session.getTrack() == &track);
    }
}