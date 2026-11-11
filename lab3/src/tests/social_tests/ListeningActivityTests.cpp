#include <catch2/catch_test_macros.hpp>
#include "ListeningActivity.h"
#include "Track.h"

TEST_CASE("ListeningActivity: Recent check and Getters") {
    Track track(1, "Song", 1, 1, 1000, nullptr);
    ListeningActivity activity("user1", &track, 1000);

    SECTION("Event within the window is recent") {
        REQUIRE(activity.isRecent(1200, 300) == true);
    }

    SECTION("Event exactly on the window boundary is recent") {
        REQUIRE(activity.isRecent(1500, 500) == true);
    }

    SECTION("Event outside the window is not recent") {
        REQUIRE(activity.isRecent(2000, 500) == false);
    }

    SECTION("Getters return correct values") {
        REQUIRE(activity.getUserId() == "user1");
        REQUIRE(activity.getListenedAt() == 1000);
    }
}