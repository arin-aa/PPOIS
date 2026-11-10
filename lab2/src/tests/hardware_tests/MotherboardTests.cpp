#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "Motherboard.h"
#include "CPU.h"
#include "RAM.h"

TEST_CASE("Motherboard: CPU and RAM installation") {
    Motherboard board("LGA1700", 2);
    CPU cpu("LGA1700", 8, 3.0);
    RAM ram1(16, 3200);
    RAM ram2(8, 3200);

    SECTION("Install valid CPU") {
        REQUIRE_NOTHROW(board.installCpu(&cpu));
    }

    SECTION("Install RAM up to capacity") {
        board.installRam(&ram1);
        board.installRam(&ram2);
        REQUIRE(board.freeRamGb() == 24);
        
        RAM ram3(8, 3200);
        REQUIRE_THROWS_AS(board.installRam(&ram3), InvalidConfigurationException);
    }
}