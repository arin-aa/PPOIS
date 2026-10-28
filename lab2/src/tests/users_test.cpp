#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"

#include "User.h"
#include "Technician.h"
#include "RepairTicket.h"

#include "Computer.h"
#include "Motherboard.h"
#include "PSU.h"
#include "Component.h"
#include "Inventory.h"

static Computer* createValidComputer(Motherboard** outBoard, PSU** outPsu) {
    *outBoard = new Motherboard("LGA1700", 2);
    *outPsu = new PSU(500, "Gold");
    
    Computer* pc = new Computer("test-pc");
    pc->assemble(*outBoard, *outPsu);
    return pc;
}

TEST_CASE("User: Authentication and Blocking") {
    User user("ivanov", "secret1");

    SECTION("Successful authentication resets fails") {
        REQUIRE(user.authenticate("secret1") == true);
    }

    SECTION("Wrong password returns false and increments fails") {
        REQUIRE(user.authenticate("wrong") == false);
        REQUIRE(user.authenticate("wrong") == false);
        REQUIRE(user.authenticate("secret1") == true); 
        REQUIRE(user.authenticate("wrong") == false);  
    }

    SECTION("3 wrong passwords block the user") {
        REQUIRE(user.authenticate("wrong") == false);
        REQUIRE(user.authenticate("wrong") == false);
        REQUIRE(user.authenticate("wrong") == false); 
        
        REQUIRE_THROWS_AS(user.authenticate("secret1"), UnauthorizedAccessException);
    }
}

TEST_CASE("User: Changing Password") {
    User user("ivanov", "secret1");

    SECTION("Change with wrong old password throws") {
        REQUIRE_THROWS_AS(user.changePassword("wrong", "newPass123"), UnauthorizedAccessException);
    }

    SECTION("Change with short new password throws") {
        REQUIRE_THROWS_AS(user.changePassword("secret1", "12345"), InvalidConfigurationException);
    }

    SECTION("Successful password change") {
        REQUIRE_NOTHROW(user.changePassword("secret1", "newSecret"));
        REQUIRE(user.authenticate("newSecret") == true);
    }
}

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

TEST_CASE("Default Constructors") {
    REQUIRE_NOTHROW(User());
    REQUIRE_NOTHROW(Technician());
    REQUIRE_NOTHROW(RepairTicket());
}