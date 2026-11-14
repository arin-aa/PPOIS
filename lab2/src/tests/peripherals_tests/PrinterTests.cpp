#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Printer.h"
#include "Port.h"
#include "Cable.h"
#include "File.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Printer: Paper, Ink and Printing") {
    Printer prn(10, 10); 
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);
    prn.connectTo(port);

    File doc("document.txt", 5, false); 

    SECTION("Load paper respects MAX_PAPER (250)") {
        REQUIRE(prn.loadPaper(10) == 20); 
        REQUIRE(prn.loadPaper(300) == 250); 
    }

    SECTION("Print successful") {
        int pagesPrinted = prn.print(&doc);
        REQUIRE(pagesPrinted > 0);
    }

    SECTION("Print throws if out of paper") {
        Printer emptyPrn(0, 10);
        emptyPrn.connectTo(port);
        REQUIRE_THROWS_AS(emptyPrn.print(&doc), PeripheralNotRespondingException);
    }

    SECTION("Print throws if out of ink") {
        Printer noInkPrn(10, 0);
        noInkPrn.connectTo(port);
        REQUIRE_THROWS_AS(noInkPrn.print(&doc), PeripheralNotRespondingException);
    }
    
    delete port;
    delete cable;
}