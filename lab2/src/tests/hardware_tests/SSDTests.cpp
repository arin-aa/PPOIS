#include <catch2/catch_test_macros.hpp>
#include "SSD.h"

TEST_CASE("SSD: Trim and Wear") {
    SSD ssd(256);

    SECTION("Trim reduces used space") {
        ssd.write(100);
        REQUIRE(ssd.trim() > 0); 
    }

    SECTION("Life left calculates wear") {
        for(int i=0; i<100; i++) ssd.write(1);
        REQUIRE(ssd.lifeLeft() == 0); 
    }
}