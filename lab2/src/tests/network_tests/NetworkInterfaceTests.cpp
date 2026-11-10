#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "IpAddress.h"
#include "NetworkInterface.h"

TEST_CASE("NetworkInterface: Connection and Errors") {
    NetworkInterface nic(1000); 

    SECTION("Transmit without connection throws") {
        REQUIRE_THROWS_AS(nic.transmitNs(100), NetworkDisconnectedException);
    }

    SECTION("Connect with invalid IP throws") {
        IpAddress badIp("invalid", 24);
        REQUIRE_THROWS_AS(nic.connect(&badIp), InvalidAddressException);
    }

    SECTION("Connect with valid IP succeeds") {
        IpAddress validIp("10.0.0.1", 24);
        REQUIRE_NOTHROW(nic.connect(&validIp));
        REQUIRE_NOTHROW(nic.transmitNs(800));
    }
}

TEST_CASE("NetworkInterface: Transmission Speed") {
    NetworkInterface nic(1000); 
    IpAddress validIp("10.0.0.1", 24);
    nic.connect(&validIp);

    SECTION("Calculate nanoseconds correctly") {
        REQUIRE(nic.transmitNs(800) == 800);
    }

    SECTION("Negative or zero speed constructor") {
        NetworkInterface badNic(-50);
        NetworkInterface nic1(1); 
        IpAddress ip("10.0.0.1", 24);
        badNic.connect(&ip);
        nic1.connect(&ip);
        
        REQUIRE(badNic.transmitNs(10) == nic1.transmitNs(10));
    }
}