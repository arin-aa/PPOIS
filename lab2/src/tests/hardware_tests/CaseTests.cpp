#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "Case.h"
#include "Fan.h"

TEST_CASE("Case: Fans and Dust") {
    Case pcCase(2); 
    Fan fan1(120, 1000);
    Fan fan2(120, 1000);
    Fan fan3(120, 1000);

    SECTION("Add fan up to limit, third throws") {
        pcCase.addFan(&fan1);
        pcCase.addFan(&fan2);
        REQUIRE_THROWS_AS(pcCase.addFan(&fan3), InvalidConfigurationException);
    }

    SECTION("Airflow with dust reduction") {
        Case bigCase(20);
        for(int i=0; i<11; i++) {
            bigCase.addFan(&fan1);
        }
        REQUIRE(bigCase.totalAirflow() == 6600); 
    }
}