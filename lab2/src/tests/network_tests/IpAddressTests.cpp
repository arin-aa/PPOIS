#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "IpAddress.h"

TEST_CASE("IpAddress: Parsing and Validation") {
    SECTION("Valid IP address passes validation") {
        IpAddress validIp("192.168.1.1", 24);
        REQUIRE_NOTHROW(validIp.validate());
    }

    SECTION("Malformed IP string throws exception") {
        REQUIRE_THROWS_AS(IpAddress("192.168.1", 24).validate(), InvalidAddressException);
        REQUIRE_THROWS_AS(IpAddress("192.168.1.a", 24).validate(), InvalidAddressException);
        REQUIRE_THROWS_AS(IpAddress("192.168.1.1.1", 24).validate(), InvalidAddressException);
    }

    SECTION("Octets out of bounds throw exception") {
        REQUIRE_THROWS_AS(IpAddress("192.168.1.256", 24).validate(), InvalidAddressException);
        REQUIRE_THROWS_AS(IpAddress("192.168.1.-5", 24).validate(), InvalidAddressException);
    }
}

TEST_CASE("IpAddress: Subnet Comparison") {
    IpAddress ip("192.168.1.10", 24);

    SECTION("Same subnet returns true") {
        REQUIRE(ip.sameSubnet("192.168.1.20") == true);
    }

    SECTION("Different subnet returns false") {
        REQUIRE(ip.sameSubnet("192.168.2.10") == false);
    }

    SECTION("Comparison with malformed IP throws") {
        REQUIRE_THROWS_AS(ip.sameSubnet("not-an-ip"), InvalidAddressException);
    }

    SECTION("Different mask length") {
        IpAddress ip16("192.168.1.10", 16);
        REQUIRE(ip16.sameSubnet("192.168.2.10") == true);
        REQUIRE(ip16.sameSubnet("192.169.1.10") == false);
    }
}