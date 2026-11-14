#include <catch2/catch_test_macros.hpp>
#include "UserFeed.h"
#include "Follow.h"
#include "ListeningActivity.h"
#include "Track.h"

TEST_CASE("UserFeed: Build feed logic") {
    Track track(1, "Song", 1, 1, 1000, nullptr);

    Follow f1("me", "friend1", 0);
    Follow f2("me", "friend2", 0);
    std::vector<Follow*> follows = {&f1, &f2};

    UserFeed feed("me", follows);

    ListeningActivity a1("friend1", &track, 1000);
    ListeningActivity a2("friend2", &track, 2000);
    ListeningActivity a3("stranger", &track, 1500);
    ListeningActivity a4("friend1", &track, 500);

    std::vector<ListeningActivity*> activities = {&a1, &a2, &a3, &a4};

    SECTION("Empty feed if no follows") {
        UserFeed emptyFeed("me", {});
        REQUIRE(emptyFeed.build(activities, 3000, 10000).empty());
    }

    SECTION("Filters by follows and time, and sorts descending by time") {
        auto result = feed.build(activities, 3000, 2100);
        
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == &a2);
        REQUIRE(result[1] == &a1);
    }

    SECTION("Filters out all old activities") {
        auto result = feed.build(activities, 3000, 100);
        REQUIRE(result.empty());
    }
    
    SECTION("Single activity insertion") {
        std::vector<ListeningActivity*> single = {&a2};
        auto result = feed.build(single, 3000, 2000);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == &a2);
    }
}