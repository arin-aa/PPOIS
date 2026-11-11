#include <catch2/catch_test_macros.hpp>
#include "ListeningActivity.h"
#include "Track.h"

TEST_CASE("ListeningActivity: Recent check and Getters") {
    Track track(1, "Song", 1, 1, 1000, nullptr);
    // Слушал в момент 1000
    ListeningActivity activity("user1", &track, 1000);

    SECTION("Event within the window is recent") {
        // now = 1200, window = 300. (1200 - 1000 = 200 <= 300) -> true
        REQUIRE(activity.isRecent(1200, 300) == true);
    }

    SECTION("Event exactly on the window boundary is recent") {
        // now = 1500, window = 500. (1500 - 1000 = 500 <= 500) -> true
        REQUIRE(activity.isRecent(1500, 500) == true);
    }

    SECTION("Event outside the window is not recent") {
        // now = 2000, window = 500. (2000 - 1000 = 1000 <= 500) -> false
        REQUIRE(activity.isRecent(2000, 500) == false);
    }

    SECTION("Getters return correct values") {
        REQUIRE(activity.getUserId() == "user1");
        REQUIRE(activity.getListenedAt() == 1000);
    }
}