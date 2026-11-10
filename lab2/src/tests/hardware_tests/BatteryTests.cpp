#include <catch2/catch_test_macros.hpp>
#include "Battery.h"

TEST_CASE("Battery: Charge and Runtime") {
    Battery bat(100, 50);

    SECTION("Charge caps at 100") {
        REQUIRE(bat.charge(20) == 70);
        REQUIRE(bat.charge(50) == 100); 
    }

    SECTION("Runtime zero watts") {
        REQUIRE(bat.runtimeMinutes(0) == 0);
    }

    SECTION("Runtime normal") {
        REQUIRE(bat.runtimeMinutes(50) == 60);
    }
}