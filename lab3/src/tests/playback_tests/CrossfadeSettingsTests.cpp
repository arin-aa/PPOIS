#include <catch2/catch_test_macros.hpp>
#include "CrossfadeSettings.h"

TEST_CASE("CrossfadeSettings: isEnabled") {
    SECTION("Positive duration means enabled") {
        CrossfadeSettings crossfade(1000);
        REQUIRE(crossfade.isEnabled() == true);
    }

    SECTION("Zero or negative duration means disabled") {
        CrossfadeSettings zero(0);
        CrossfadeSettings negative(-500);
        REQUIRE(zero.isEnabled() == false);
        REQUIRE(negative.isEnabled() == false);
    }
}