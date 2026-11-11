#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "DiagnosticService.h"
#include "Logger.h"
#include "Computer.h"
#include "Motherboard.h"
#include "PSU.h"
#include "SSD.h"

static Computer* createValidComputer(Motherboard** outBoard, PSU** outPsu, SSD** outDisk) {
    *outBoard = new Motherboard("LGA1700", 2);
    *outPsu = new PSU(500, "Gold");
    *outDisk = new SSD(100);
    
    Computer* pc = new Computer("test-pc");
    pc->assemble(*outBoard, *outPsu);
    pc->addStorage(*outDisk);
    return pc;
}

TEST_CASE("DiagnosticService: Scanning and Health") {
    Logger logger("INFO", 10);
    
    Motherboard* board = nullptr; 
    PSU* psu = nullptr; 
    SSD* disk = nullptr;
    Computer* pc = createValidComputer(&board, &psu, &disk);

    SECTION("No issues detected") {
        DiagnosticService diag(300, 50, &logger); 
        REQUIRE(diag.scan(pc) == 0); 
        REQUIRE(diag.healthScore() == 100);
    }

    SECTION("Low power reserve detected") {
        DiagnosticService diag(450, 50, &logger); 
        REQUIRE(diag.scan(pc) == 1);
        REQUIRE(diag.healthScore() == 75); 
    }

    SECTION("Low disk space detected") {
        DiagnosticService diag(300, 200, &logger); 
        REQUIRE(diag.scan(pc) == 1);
        REQUIRE(diag.healthScore() == 75);
    }

    SECTION("Both issues detected, multiple scans") {
        DiagnosticService diag(450, 200, &logger);
        REQUIRE(diag.scan(pc) == 2);
        REQUIRE(diag.scan(pc) == 4); 
        diag.scan(pc);
        REQUIRE(diag.healthScore() == 0); 
    }

    delete pc;
    delete board;
    delete psu;
    delete disk;
}