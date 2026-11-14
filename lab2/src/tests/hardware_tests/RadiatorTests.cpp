#include <catch2/catch_test_macros.hpp>
#include "Radiator.h"

TEST_CASE("Radiator: Refill") {
    SECTION("Radiator refill caps at capacity") {
        Radiator rad(100, 200); 
        REQUIRE(rad.refill(150) == 150); 
        REQUIRE(rad.refill(100) == 200); 
    }
}