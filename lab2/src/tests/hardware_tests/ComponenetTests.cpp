#include <catch2/catch_test_macros.hpp>
#include "Component.h"

TEST_CASE("Component: Basic behavior") {
    Component comp("CPU", "Intel", 100);

    SECTION("isNamed checks name and manufacturer") {
        REQUIRE(comp.isNamed("CPU") == true);
        REQUIRE(comp.isNamed("Intel") == true);
        REQUIRE(comp.isNamed("AMD") == false);
    }

    SECTION("draw calculates load") {
        REQUIRE(comp.draw(50) == 50); 
        REQUIRE(comp.draw(0) == 0);
    }
}