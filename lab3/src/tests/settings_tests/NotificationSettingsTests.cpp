#include <catch2/catch_test_macros.hpp>
#include "NotificationSettings.h"

TEST_CASE("NotificationSettings: Mute All") {
    SECTION("Mute All does not crash") {
        NotificationSettings settings(true, true);
        REQUIRE_NOTHROW(settings.muteAll());
    }

    SECTION("Mute All on already muted settings does not crash") {
        NotificationSettings settings(false, false);
        REQUIRE_NOTHROW(settings.muteAll());
    }
}