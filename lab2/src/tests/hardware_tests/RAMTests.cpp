#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "RAM.h"

TEST_CASE("RAM: Allocation and Limits") {
    RAM ram(16, 3200);

    SECTION("Free space") {
        REQUIRE(ram.freeGb() == 16);
    }

    SECTION("Allocate successful") {
        REQUIRE(ram.allocate(8) > 0); 
        REQUIRE(ram.freeGb() == 8);
    }

    SECTION("Allocate overflow throws") {
        REQUIRE_THROWS_AS(ram.allocate(17), MemoryOverflowException);
    }
}