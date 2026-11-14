#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "SleepTimer.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("SleepTimer: Start") {
    SleepTimer timer;

    SECTION("Zero or negative duration throws") {
        REQUIRE_THROWS_AS(timer.start(0), PlaybackException);
        REQUIRE_THROWS_AS(timer.start(-100), PlaybackException);
    }

    SECTION("Positive duration starts the timer") {
        REQUIRE_NOTHROW(timer.start(5000));
    }
}