#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "IpAddress.h"
#include "MacAddress.h"
#include "NetworkInterface.h"
#include "Packet.h"

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

TEST_CASE("Packet: Forwarding and TTL") {
    IpAddress source("192.168.0.10", 24);

    SECTION("Forward valid packet decreases TTL and returns bits") {
        Packet p(&source, "192.168.0.20", 512, 2);
        REQUIRE(p.forward() == 4096);
    }

    SECTION("Forward expired packet throws") {
        Packet p(&source, "192.168.0.20", 512, 0);
        REQUIRE_THROWS_AS(p.forward(), NetworkDisconnectedException);
        
        Packet pNeg(&source, "192.168.0.20", 512, -1);
        REQUIRE_THROWS_AS(pNeg.forward(), NetworkDisconnectedException);
    }
}

TEST_CASE("Packet: Locality") {
    IpAddress source("192.168.0.10", 24);

    SECTION("Local packet (same subnet)") {
        Packet local(&source, "192.168.0.20", 512, 1);
        REQUIRE(local.isLocal() == true);
    }

    SECTION("Remote packet (different subnet)") {
        Packet remote(&source, "10.0.0.1", 512, 1);
        REQUIRE(remote.isLocal() == false);
    }
}