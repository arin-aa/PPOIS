#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "Server.h"
#include "ComputerExceptions.h"
#include "NetworkInterface.h"
#include "Packet.h"
#include "IpAddress.h"

TEST_CASE("Server: RAID and Requests", "[Server]") {
    IpAddress ip("192.168.0.10", 24);
    NetworkInterface nic(1000);
    nic.connect(&ip); 
    Packet packet(&ip, "192.168.0.20", 512, 1);
    
    Server server("web-01", 2, &nic);

    SECTION("Valid RAID levels return correct usable percentage") {
        REQUIRE(server.configureRaid("RAID0") == 100);
        REQUIRE(server.configureRaid("RAID1") == 50);
        REQUIRE(server.configureRaid("RAID5") == 67);
    }

    SECTION("Invalid RAID level throws exception") {
        REQUIRE_THROWS_AS(server.configureRaid("RAID9"), InvalidConfigurationException);
    }

    SECTION("HandleRequest increments counter and transmits") {
        REQUIRE_NOTHROW(server.handleRequest(&packet));
    }
    
    SECTION("Power draw includes NIC and Rack units") {
        REQUIRE(server.powerDraw() >= 30 + 10 + (2 * 15));
    }
}

TEST_CASE("Server: Exception without NIC", "[Server]") {
    Server emptyServer;
    IpAddress ip("192.168.0.10", 24);
    Packet packet(&ip, "192.168.0.20", 512, 1);

    REQUIRE_THROWS_AS(emptyServer.handleRequest(&packet), NetworkDisconnectedException);
}