#include <catch2/catch_test_macros.hpp>
#include "Device.h"

TEST_CASE("Device: Online Status and Touch") {
    // ONLINE_TIMEOUT_MS = 300000
    Device device("d1", "Phone", "android", 1000, "token");

    SECTION("Device is online within timeout") {
        REQUIRE(device.isOnline(1000) == true);
        REQUIRE(device.isOnline(301000) == true); // ровно на границе (300000 разница)
    }

    SECTION("Device is offline outside timeout") {
        REQUIRE(device.isOnline(301001) == false);
    }

    SECTION("Touch updates lastActiveAt") {
        device.touch(5000);
        // Теперь последняя активность 5000
        REQUIRE(device.isOnline(6000) == true);
        REQUIRE(device.isOnline(305001) == false); // 305001 - 5000 > 300000
    }
}