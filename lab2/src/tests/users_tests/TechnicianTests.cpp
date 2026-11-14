#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Technician.h"
#include "Component.h"
#include "Inventory.h"

TEST_CASE("Technician: Estimate and Ordering") {
    Technician hwTech("ivanov", "pass", "hardware", 5);
    Technician swTech("petrov", "pass", "software", 2);

    SECTION("Estimate calculation for hardware vs software") {
        REQUIRE(hwTech.estimate(10) == 400); 
        REQUIRE(swTech.estimate(10) == 240); 
    }

    SECTION("Order part from stock") {
        Inventory stock("Main", 10);
        Component part("GPU", "Nvidia", 200);
        stock.addItem(&part);

        Component* found = hwTech.orderPart(&stock, "GPU");
        REQUIRE(found == &part);
    }

    SECTION("Order missing part throws") {
        Inventory stock("Main", 10);
        REQUIRE_THROWS_AS(hwTech.orderPart(&stock, "CPU"), InvalidConfigurationException);
    }
}

TEST_CASE("Technician: Default constructor") {
    REQUIRE_NOTHROW(Technician());
}