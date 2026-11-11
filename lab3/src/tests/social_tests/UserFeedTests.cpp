#include <catch2/catch_test_macros.hpp>
#include "UserFeed.h"
#include "Follow.h"
#include "ListeningActivity.h"
#include "Track.h"

TEST_CASE("UserFeed: Build feed logic") {
    Track track(1, "Song", 1, 1, 1000, nullptr);

    // Пользователь "me" подписан на "friend1" и "friend2"
    Follow f1("me", "friend1", 0);
    Follow f2("me", "friend2", 0);
    std::vector<Follow*> follows = {&f1, &f2};

    UserFeed feed("me", follows);

    // Активности:
    // 1. friend1 в 1000 (старая)
    // 2. friend2 в 2000 (новая)
    // 3. stranger в 1500 (не подписан, игнорируется)
    // 4. friend1 в 500 (слишком старая)
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
        // now = 3000, window = 1500.
        // a4: 3000 - 500 = 2500 > 1500 -> игнорируется (старая)
        // a3: не подписан -> игнорируется
        // a1: 3000 - 1000 = 2000 <= 1500 -> ОШИБКА! 2000 > 1500. Тоже старая!
        
        // Давай сделаем окно больше, чтобы a1 попала: window = 2500
        auto result = feed.build(activities, 3000, 2100);
        
        // Должны остаться: a1 (1000) и a2 (2000).
        // Ожидаемая сортировка: сначала a2 (2000), потом a1 (1000).
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == &a2);
        REQUIRE(result[1] == &a1);
    }

    SECTION("Filters out all old activities") {
        // window = 100 (никто не попадает, так как самая новая в 2000, а now=3000)
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