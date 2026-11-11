#include <catch2/catch_test_macros.hpp>

#include "Logger.h"

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