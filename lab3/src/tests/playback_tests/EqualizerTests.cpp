#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Equalizer.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("Equalizer: Presets and Bands") {
    Equalizer eq;

    SECTION("Apply valid presets") {
        REQUIRE_NOTHROW(eq.applyPreset("flat"));
        REQUIRE_NOTHROW(eq.applyPreset("bass"));
        REQUIRE_NOTHROW(eq.applyPreset("treble"));
    }

    SECTION("Apply invalid preset throws") {
        REQUIRE_THROWS_AS(eq.applyPreset("jazz"), AudioEngineException);
    }

    SECTION("Set valid band gain") {
        REQUIRE_NOTHROW(eq.setBandGain(0, 5));
        REQUIRE_NOTHROW(eq.setBandGain(9, -12));
    }

    SECTION("Invalid band index throws") {
        REQUIRE_THROWS_AS(eq.setBandGain(-1, 0), AudioEngineException);
        REQUIRE_THROWS_AS(eq.setBandGain(10, 0), AudioEngineException);
    }

    SECTION("Invalid gain value throws") {
        REQUIRE_THROWS_AS(eq.setBandGain(0, -13), AudioEngineException);
        REQUIRE_THROWS_AS(eq.setBandGain(0, 13), AudioEngineException);
    }
}