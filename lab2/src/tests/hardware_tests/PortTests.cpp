#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "Port.h"
#include "Cable.h"

TEST_CASE("Port: Plug and Throughput") {
    Port port("USB", 480);
    Cable slowCable("USB", 2.0, 400); 
    Cable fastCable("USB", 1.0, 1000); 

    SECTION("No cable throws") {
        REQUIRE_THROWS_AS(port.throughput(), PeripheralNotRespondingException);
    }

    SECTION("Throughput limits by cable or port") {
        port.plug(&slowCable);
        REQUIRE(port.throughput() == 300); 

        port.plug(&fastCable);
        REQUIRE(port.throughput() == 480);
    }
}