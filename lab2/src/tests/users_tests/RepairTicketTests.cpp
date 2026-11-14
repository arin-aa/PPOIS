#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "RepairTicket.h"
#include "Technician.h"
#include "Computer.h"
#include "Motherboard.h"
#include "PSU.h"

static Computer* createValidComputer(Motherboard** outBoard, PSU** outPsu) {
    *outBoard = new Motherboard("LGA1700", 2);
    *outPsu = new PSU(500, "Gold");
    
    Computer* pc = new Computer("test-pc");
    pc->assemble(*outBoard, *outPsu);
    return pc;
}

TEST_CASE("RepairTicket: Lifecycle") {
    Motherboard* board = nullptr;
    PSU* psu = nullptr;
    Computer* pc = createValidComputer(&board, &psu);
    
    RepairTicket ticket("Screen flickering", pc);
    Technician tech("ivanov", "secret1", "hardware", 5);

    SECTION("Diagnose returns power reserve") {
        REQUIRE(ticket.diagnose() > 0);
    }

    SECTION("Assign technician") {
        REQUIRE_NOTHROW(ticket.assign(&tech));
        REQUIRE_THROWS_AS(ticket.assign(&tech), InvalidConfigurationException);
    }

    SECTION("Close ticket without technician throws") {
        REQUIRE_THROWS_AS(ticket.close(3), UnauthorizedAccessException);
    }

    SECTION("Close ticket with technician calculates cost") {
        ticket.assign(&tech);
        
        REQUIRE(ticket.close(3) == 120);
        
        REQUIRE_THROWS_AS(ticket.close(1), UnauthorizedAccessException);
    }

    delete pc;
    delete board;
    delete psu;
}

TEST_CASE("RepairTicket: Default constructor") {
    REQUIRE_NOTHROW(RepairTicket());
}