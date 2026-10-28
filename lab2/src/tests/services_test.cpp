#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"

#include "CompatibilityChecker.h"
#include "DiagnosticService.h"
#include "Inventory.h"
#include "Logger.h"
#include "ReportGenerator.h"
#include "SystemBuilder.h"

#include "Component.h"
#include "Computer.h"
#include "Motherboard.h"
#include "PSU.h"
#include "SSD.h"
#include "File.h"

static Computer* createValidComputer(Motherboard** outBoard, PSU** outPsu, SSD** outDisk) {
    *outBoard = new Motherboard("LGA1700", 2);
    *outPsu = new PSU(500, "Gold");
    *outDisk = new SSD(100);
    
    Computer* pc = new Computer("test-pc");
    pc->assemble(*outBoard, *outPsu);
    pc->addStorage(*outDisk);
    return pc;
}

TEST_CASE("CompatibilityChecker: Power checking") {
    SECTION("Normal mode (not strict)") {
        CompatibilityChecker checker(false, 100);
        REQUIRE(checker.checkPower(500, 450) == 50);
    }

    SECTION("Strict mode: sufficient reserve") {
        CompatibilityChecker checker(true, 100);
        REQUIRE(checker.checkPower(500, 350) == 150);
    }

    SECTION("Strict mode: insufficient reserve throws") {
        CompatibilityChecker checker(true, 100);
        REQUIRE_THROWS_AS(checker.checkPower(500, 450), InsufficientPowerException);
    }
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

TEST_CASE("Inventory: Adding and Taking Items") {
    Inventory stock("Main", 2);
    Component item1("Fan", "Noctua", 5);
    Component item2("CPU", "Intel", 65);
    Component item3("GPU", "Nvidia", 200);

    SECTION("Add items up to capacity") {
        REQUIRE(stock.addItem(&item1) == 1);
        REQUIRE(stock.addItem(&item2) == 2);
        REQUIRE_THROWS_AS(stock.addItem(&item3), InventoryFullException);
    }

    SECTION("Take existing item") {
        stock.addItem(&item1);
        stock.addItem(&item2);
        
        Component* found = stock.takeItem("Fan");
        REQUIRE(found == &item1);
        REQUIRE_NOTHROW(stock.addItem(&item3));
    }

    SECTION("Take missing item returns nullptr") {
        stock.addItem(&item1);
        Component* found = stock.takeItem("RAM");
        REQUIRE(found == nullptr);
    }
}

TEST_CASE("Logger: Logging and Tail") {
    SECTION("Logger with default max entries (if maxEntries <= 0)") {
        Logger logger("WARN", -5);
        logger.log("msg1");
        logger.log("msg2"); 
        REQUIRE(logger.tail(5) == "[WARN] msg2");
    }

    SECTION("Basic logging without drops") {
        Logger logger("INFO", 3);
        logger.log("A");
        logger.log("B");
        REQUIRE(logger.tail(2) == "[INFO] A; [INFO] B");
    }

    SECTION("Logging drops oldest when full") {
        Logger logger("INFO", 2);
        logger.log("A");
        logger.log("B");
        logger.log("C"); 
        REQUIRE(logger.tail(2) == "[INFO] B; [INFO] C");
    }

    SECTION("Tail edge cases") {
        Logger logger("INFO", 5);
        logger.log("A");
        
        REQUIRE(logger.tail(0) == "");        
        REQUIRE(logger.tail(10) == "[INFO] A"); 
    }
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

TEST_CASE("SystemBuilder: Budget and Power Calculations") {
    CompatibilityChecker checker(true, 100); 
    SystemBuilder builder(1000, &checker);   

    SECTION("Add parts within budget") {
        builder.addPart(100, 500); 
        builder.addPart(50, 400);  
        REQUIRE(builder.recommendedPsu() == 250);
    }

    SECTION("Add parts exceeding budget throws") {
        builder.addPart(100, 500);
        REQUIRE_THROWS_AS(builder.addPart(50, 600), InvalidConfigurationException);
    }

    SECTION("Power margin calculation") {
        builder.addPart(100, 500);
        REQUIRE(builder.powerMargin(300) == 200);
        REQUIRE_THROWS_AS(builder.powerMargin(150), InsufficientPowerException);
    }
}