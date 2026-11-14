#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "Cable.h"

TEST_CASE("Cable: Match and Speed Loss") {
    SECTION("Match throws on mismatch") {
        Cable cable("USB", 1.0, 500);
        REQUIRE_NOTHROW(cable.match("USB"));
        REQUIRE_THROWS_AS(cable.match("HDMI"), InvalidConfigurationException);
    }

    SECTION("Effective Mbps") {
        Cable fastCable("USB", 2.0, 500); 
        Cable slowCable("USB", 20.0, 500); 
        
        REQUIRE(fastCable.effectiveMbps() == 400);
        REQUIRE(slowCable.effectiveMbps() == 0);
    }
}