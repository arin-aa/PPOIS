#include <catch2/catch_test_macros.hpp>
#include "NVMe.h"

TEST_CASE("NVMe: Read speed cap") {
    SECTION("Queue depth below max") {
        NVMe nvme(512, 4, 16);
        REQUIRE(nvme.readSpeed() == 1800);
    }

    SECTION("Queue depth above max (caps at 32)") {
        NVMe nvme(512, 4, 64);
        REQUIRE(nvme.readSpeed() == 3600);
    }
}