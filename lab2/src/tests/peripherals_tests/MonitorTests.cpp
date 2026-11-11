#include <catch2/catch_test_macros.hpp>

#include "Monitor.h"

TEST_CASE("Monitor: Brightness and Megapixels") {
    Monitor mon(1920, 1080);

    SECTION("Adjust brightness normal") {
        REQUIRE(mon.adjustBrightness(20) == 70);
        REQUIRE(mon.adjustBrightness(-10) == 60);
    }

    SECTION("Brightness caps at 0 (lower bound)") {
        REQUIRE(mon.adjustBrightness(-100) == 0);
    }

    SECTION("Brightness caps at 100 (upper bound)") {
        REQUIRE(mon.adjustBrightness(100) == 100);
    }

    SECTION("Megapixels calculation") {
        REQUIRE(mon.megapixels() > 2.0);
    }
}