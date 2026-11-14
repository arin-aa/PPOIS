#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "PlaybackState.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

TEST_CASE("PlaybackState: Position and Flags") {
    PlaybackState state;
    Track track(1, "Song", 1, 1, 1000, nullptr);

    SECTION("updatePosition throws on negative") {
        REQUIRE_THROWS_AS(state.updatePosition(-1), PlaybackException);
    }

    SECTION("updatePosition clamps to track duration") {
        state.setTrack(&track);
        REQUIRE(state.updatePosition(1500) == 1000); 
    }

    SECTION("toggleShuffle switches state") {
        REQUIRE(state.toggleShuffle() == true);
        REQUIRE(state.toggleShuffle() == false);
    }

    SECTION("Setters and getters") {
        state.setTrack(&track);
        state.setPlaying(true);
        
        REQUIRE(state.getCurrentTrack() == &track);
        REQUIRE(state.getPositionMs() == 0);
    }
}