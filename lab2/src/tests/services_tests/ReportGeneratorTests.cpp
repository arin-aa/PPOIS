#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "ReportGenerator.h"
#include "File.h"
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

TEST_CASE("ReportGenerator: Generate and Save") {
    Motherboard* board = nullptr; 
    PSU* psu = nullptr; 
    SSD* disk = nullptr;
    Computer* pc = createValidComputer(&board, &psu, &disk);
    
    ReportGenerator generator("PDF", "Ivanov");
    File file("report.pdf", 10, false);

    SECTION("Generate report string") {
        std::string report = generator.generate(pc);
      
        REQUIRE(report.find("[PDF #1 by Ivanov]") != std::string::npos);
        REQUIRE(report.find("draw=") != std::string::npos);
        REQUIRE(report.find("reserve=") != std::string::npos);
        REQUIRE(report.find("free=") != std::string::npos);
        
        std::string report2 = generator.generate(pc);
        REQUIRE(report2.find("[PDF #2 by Ivanov]") != std::string::npos);
    }

    SECTION("Save report to file") {
        std::string text = "Hello Report";
        REQUIRE_NOTHROW(generator.save(text, &file));
    }

    delete pc;
    delete board;
    delete psu;
    delete disk;
}