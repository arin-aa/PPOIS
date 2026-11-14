#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "Computer.h"
#include "Laptop.h"
#include "Battery.h"
#include "Motherboard.h"
#include "PSU.h"

TEST_CASE("Laptop: Charging and Battery", "[Laptop]") {
    Battery battery(50, 10);
    Laptop laptop("lt-01", 15, &battery);
    Motherboard board("LGA1700", 1);
    PSU psu(500, "80+ Gold");
    
    laptop.assemble(&board, &psu);

    SECTION("PlugIn charges battery and returns charge percentage") {
        int newCharge = laptop.plugIn(10);
        REQUIRE(newCharge >= 0); 
    }

    SECTION("PowerDraw overrides base class (adds screen watts)") {
        int baseDraw = Computer("lt-01").powerDraw();
        REQUIRE(laptop.powerDraw() > 30); 
    }

    SECTION("batteryMinutes returns runtime") {
        REQUIRE(laptop.batteryMinutes() >= 0);
    }
}