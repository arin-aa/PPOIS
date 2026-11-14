#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "GPU.h"

TEST_CASE("GPU: Render Time and VRAM Limits") {
    GPU gpu(8, 1000); 

    SECTION("Render overflow throws") {
        REQUIRE_THROWS_AS(gpu.renderTime(801), MemoryOverflowException);
    }

    SECTION("Render normal") {
        REQUIRE(gpu.renderTime(100) == 100.0);
    }
}