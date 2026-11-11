#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "OfflineCache.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("OfflineCache: Put, Get and Eviction") {
    OfflineCache cache(100, 1000); // maxSize=100, ttl=1000

    SECTION("Put throws if file is larger than max size") {
        REQUIRE_THROWS_AS(cache.put(1, 101, 0), DownloadException);
    }

    SECTION("Get throws if track not cached") {
        REQUIRE_THROWS_AS(cache.get(99, 0), TrackNotFoundException);
    }

    SECTION("Put and Get valid track") {
        cache.put(1, 50, 0);
        REQUIRE(cache.get(1, 500) == 50);
    }

    SECTION("Overwrite existing track") {
        cache.put(1, 50, 0);
        cache.put(1, 20, 10); // Тот же ID, другой размер
        REQUIRE(cache.get(1, 20) == 20);
    }

    SECTION("Get throws and removes if expired") {
        cache.put(1, 50, 0);
        // now = 1500, ttl = 1000 -> 1500 - 0 = 1500 > 1000 (истек)
        REQUIRE_THROWS_AS(cache.get(1, 1500), TrackNotFoundException);
        
        // После этого его нет в кэше, повторный запрос тоже бросит
        REQUIRE_THROWS_AS(cache.get(1, 1500), TrackNotFoundException);
    }

    SECTION("Eviction logic removes oldest tracks when full") {
        cache.put(1, 60, 0); // size=60
        cache.put(2, 60, 10); // нужно 60. 60+60=120>100. Вытесняет 1. size=60.
        
        // Проверяем, что 1 вытеснен
        REQUIRE_THROWS_AS(cache.get(1, 20), TrackNotFoundException);
        // 2 на месте
        REQUIRE(cache.get(2, 20) == 60);
    }
}