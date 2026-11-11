#include <catch2/catch_test_macros.hpp>
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "Track.h"

TEST_CASE("PlaybackHistory: Add and Recent") {
    PlaybackHistory history("user1");
    Track track(1, "Song", 1, 1, 1000, nullptr);
    PlaybackSession session(&track, 0);

    SECTION("Add sessions and get recent") {
        history.add(session);
        history.add(session);
        
        auto recent = history.getRecent(1);
        REQUIRE(recent.size() == 1);
        
        auto all = history.getRecent(10);
        REQUIRE(all.size() == 2);
        
        REQUIRE(history.getSessions().size() == 2);
    }

    SECTION("History overflow evicts the oldest") {
        for(int i=0; i<=500; ++i) {
            history.add(session);
        }
        REQUIRE(history.getSessions().size() == 500);
    }

    SECTION("getRecent with zero or negative count returns empty") {
        history.add(session);
        REQUIRE(history.getRecent(0).empty());
        REQUIRE(history.getRecent(-5).empty());
    }
}