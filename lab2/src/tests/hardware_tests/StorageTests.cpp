#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "Storage.h"

TEST_CASE("Storage: Base write, erase, life") {
    Storage disk("HDD", 100);

    SECTION("Write successful") {
        REQUIRE_NOTHROW(disk.write(50));
        REQUIRE(disk.freeSpace() == 50);
    }

    SECTION("Write overflow throws") {
        REQUIRE_THROWS_AS(disk.write(101), DiskFullException);
    }

    SECTION("Erase branches") {
        disk.write(10);
        REQUIRE(disk.erase(5) == 5);   
        REQUIRE(disk.erase(10) == 5);  
        REQUIRE(disk.lifeLeft() == 100);
    }
}