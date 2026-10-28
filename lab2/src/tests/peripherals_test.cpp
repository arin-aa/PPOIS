#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"

#include "Peripheral.h"
#include "Keyboard.h"
#include "Monitor.h"
#include "Mouse.h"
#include "Printer.h"
#include "Scanner.h"
#include "Webcam.h"

#include "Port.h"
#include "Cable.h"
#include "File.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Peripheral: Connection and Ping") {
    Keyboard kb("EN");
    Cable* cable = nullptr;
    Port* validPort = createWorkingPort(&cable);
    Port emptyPort("USB", 480); 

    SECTION("Ping throws if not connected") {
        REQUIRE_THROWS_AS(kb.ping(), PeripheralNotRespondingException);
    }

    SECTION("ConnectTo throws if port has no cable") {
        REQUIRE_THROWS_AS(kb.connectTo(&emptyPort), PeripheralNotRespondingException);
    }

    SECTION("Successful connection and ping calculation") {
        kb.connectTo(validPort);
        REQUIRE(kb.ping() == 322); 
    }
  
    delete validPort;
    delete cable;
}

TEST_CASE("Keyboard: Layouts and Presses") {
    Keyboard kb("EN");
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);
    kb.connectTo(port);

    SECTION("Switch valid layouts") {
        REQUIRE_NOTHROW(kb.switchLayout("RU"));
        REQUIRE_NOTHROW(kb.switchLayout("DE"));
    }

    SECTION("Switch invalid layout throws") {
        REQUIRE_THROWS_AS(kb.switchLayout("FR"), InvalidConfigurationException);
    }

    SECTION("Press keys") {
        REQUIRE(kb.press(5) == 5);
        REQUIRE(kb.press(3) == 8);
    }
    
    delete port;
    delete cable;
}

TEST_CASE("Monitor: Brightness and Megapixels") {
    Monitor mon(1920, 1080);

    SECTION("Adjust brightness normal") {
        REQUIRE(mon.adjustBrightness(20) == 70);
        REQUIRE(mon.adjustBrightness(-10) == 60);
    }

    SECTION("Brightness caps at 0 (lower bound)") {
        REQUIRE(mon.adjustBrightness(-100) == 0);
    }

    SECTION("Brightness caps at 100 (upper bound)") {
        REQUIRE(mon.adjustBrightness(100) == 100);
    }

    SECTION("Megapixels calculation") {
        REQUIRE(mon.megapixels() > 2.0);
    }
}

TEST_CASE("Mouse: DPI and Clicks") {
    Mouse mouse(800);
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);
    mouse.connectTo(port);

    SECTION("Valid DPI change") {
        REQUIRE(mouse.changeDpi(16000) == 16000);
        REQUIRE(mouse.changeDpi(100) == 100);
    }

    SECTION("DPI out of bounds throws") {
        REQUIRE_THROWS_AS(mouse.changeDpi(99), InvalidConfigurationException);
        REQUIRE_THROWS_AS(mouse.changeDpi(16001), InvalidConfigurationException);
    }

    SECTION("Clicks increment") {
        REQUIRE(mouse.click() == 1);
        REQUIRE(mouse.click() == 2);
    }
    
    delete port;
    delete cable;
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

TEST_CASE("Scanner and Webcam: Operations") {
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);

    SECTION("Scanner: scan pages") {
        Scanner scn(1200, 24);
        scn.connectTo(port);
        REQUIRE(scn.scanPages(2) == 57);
    }

    SECTION("Webcam: record video") {
        Webcam cam(1080, 30);
        cam.connectTo(port);
        REQUIRE(cam.record(10) == 32);
    }
    
    delete port;
    delete cable;
}