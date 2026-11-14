#include <catch2/catch_test_macros.hpp>
#include "PSU.h"

TEST_CASE("PSU: Reserve and Wall Draw") {
    SECTION("Reserve is positive/negative") {
        PSU psu(500, "80+ Gold");
        REQUIRE(psu.reserve(400) == 100);
        REQUIRE(psu.reserve(600) == -100);
    }

    SECTION("Wall Draw calculates efficiency") {
        PSU gold(500, "80+ Gold"); 
        PSU base(500, "80+");      
        
        REQUIRE(gold.wallDraw(450) == 500); 
        REQUIRE(base.wallDraw(400) == 500); 
    }
}