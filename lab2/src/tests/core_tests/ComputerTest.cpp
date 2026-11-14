#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "Computer.h"
#include "ComputerExceptions.h"
#include "Motherboard.h"
#include "PSU.h"
#include "OperatingSystem.h"
#include "SSD.h"

TEST_CASE("Computer: Assembling and Powering On", "[Computer]") {
    Computer pc("test-pc");
    Motherboard board("LGA1700", 2);
    PSU psu(500, "80+ Gold");
    SSD disk(256);
    
    SECTION("Cannot power on if not assembled") {
        REQUIRE_THROWS_AS(pc.powerOn(), BootFailureException);
    }

    SECTION("Cannot install OS without disk") {
        OperatingSystem os("Linux", 5000);
        pc.assemble(&board, &psu);
        REQUIRE_THROWS_AS(pc.installOs(&os), InvalidConfigurationException);
    }

    SECTION("Cannot power on with weak PSU") {
        PSU weakPsu(10, "Weak"); 
        pc.assemble(&board, &weakPsu);
        REQUIRE_THROWS_AS(pc.powerOn(), InsufficientPowerException);
    }

    SECTION("Successful assembly, install OS, and power on") {
        OperatingSystem os("Linux", 5000);
        pc.assemble(&board, &psu);
        pc.addStorage(&disk);
        
        int initialFreeSpace = pc.freeStorageGb();
        REQUIRE(initialFreeSpace == 256);

        pc.installOs(&os);
        REQUIRE(pc.freeStorageGb() < initialFreeSpace); 

        REQUIRE_NOTHROW(pc.powerOn());
    }
}

TEST_CASE("Computer: Power Calculations", "[Computer]") {
    Computer pc("calc-pc");
    Motherboard board("LGA1700", 2);
    PSU psu(500, "80+ Gold");
    SSD disk(256);

    SECTION("Power draw with no components (Base only)") {
        REQUIRE(pc.powerDraw() == 30); 
    }

    SECTION("Power draw with components") {
        pc.assemble(&board, &psu);
        pc.addStorage(&disk);
        
        REQUIRE(pc.powerDraw() > 30); 
    }
    
    SECTION("Power reserve throws if no PSU") {
        REQUIRE_THROWS_AS(pc.powerReserve(), BootFailureException);
    }
}