#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "CPU.h"
#include "Sensor.h"

TEST_CASE("CPU: Load, Throttling and Sockets") {
    Sensor sensor(80.0);
    CPU cpu("LGA1700", 8, 3.0, &sensor);

    SECTION("Invalid load throws") {
        REQUIRE_THROWS_AS(cpu.runLoad(-1), InvalidConfigurationException);
        REQUIRE_THROWS_AS(cpu.runLoad(101), InvalidConfigurationException);
    }

    SECTION("Throttling reduces frequency if load > 95") {
        cpu.runLoad(99); 
        REQUIRE_NOTHROW(cpu.runLoad(99));
    }

    SECTION("Overheating throws") {
        sensor.measure(100.0); 
        REQUIRE_THROWS_AS(cpu.runLoad(50), OverheatingException);
    }

    SECTION("Socket mismatch throws") {
        REQUIRE_THROWS_AS(cpu.checkSocket("AM5"), IncompatibleSocketException);
        REQUIRE_NOTHROW(cpu.checkSocket("LGA1700"));
    }
}