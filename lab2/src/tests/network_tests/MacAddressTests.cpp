#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "MacAddress.h"

TEST_CASE("MacAddress: Verification") {
    SECTION("Valid MAC address passes") {
        MacAddress validMac("AA:BB:CC:DD:EE:FF", "Intel");
        REQUIRE_NOTHROW(validMac.verify());
    }

    SECTION("Wrong length throws") {
        MacAddress shortMac("AA:BB:CC:DD:EE", "Intel");
        REQUIRE_THROWS_AS(shortMac.verify(), InvalidAddressException);
    }

    SECTION("Wrong separator throws") {
        MacAddress dashMac("AA-BB-CC-DD-EE-FF", "Intel");
        REQUIRE_THROWS_AS(dashMac.verify(), InvalidAddressException);
    }

    SECTION("No separators throws") {
        MacAddress plainMac("AABBCCDDEEFF", "Intel");
        REQUIRE_THROWS_AS(plainMac.verify(), InvalidAddressException);
    }
}