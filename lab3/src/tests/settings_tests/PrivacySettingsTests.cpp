#include <catch2/catch_test_macros.hpp>
#include "PrivacySettings.h"

TEST_CASE("PrivacySettings: isPrivate logic") {
    SECTION("Both sharing flags ON means NOT private") {
        PrivacySettings settings(true, true);
        REQUIRE(settings.isPrivate() == false);
    }

    SECTION("Share listening ON, public playlists OFF means NOT private") {
        PrivacySettings settings(true, false);
        REQUIRE(settings.isPrivate() == false);
    }

    SECTION("Share listening OFF, public playlists ON means NOT private") {
        PrivacySettings settings(false, true);
        REQUIRE(settings.isPrivate() == false);
    }

    SECTION("Both sharing flags OFF means private") {
        PrivacySettings settings(false, false);
        REQUIRE(settings.isPrivate() == true);
    }
}