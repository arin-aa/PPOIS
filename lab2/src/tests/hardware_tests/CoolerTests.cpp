#include <catch2/catch_test_macros.hpp>
#include "Cooler.h"

TEST_CASE("Cooler: Headroom") {
    SECTION("Cooler headroom can be negative or positive") {
        Cooler cooler("Noctua", 150);
        REQUIRE(cooler.headroom(100) == 50);
        REQUIRE(cooler.headroom(200) == -50);
    }
}