#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "IpAddress.h"
#include "Packet.h"

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