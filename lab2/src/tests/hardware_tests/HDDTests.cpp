#include <catch2/catch_test_macros.hpp>
#include "HDD.h"

TEST_CASE("HDD: Defragmentation and Wear") {
    SECTION("Defragment resets fragmentation and adds bad sectors") {
        HDD hdd(1000, 7200, 50); 
        REQUIRE(hdd.defragment() > 0);
        REQUIRE(hdd.defragment() == 0);
    }

    SECTION("Life left goes negative branch") {
        HDD hdd(1000, 7200, 100); 
        hdd.defragment(); 
        REQUIRE(hdd.lifeLeft() == 75);
    }
}