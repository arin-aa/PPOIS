#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "File.h"

TEST_CASE("File: Content and Size") {
    File normalFile("notes.txt", 10, false);
    File lockedFile("locked.txt", 5, true);

    SECTION("Append to normal file") {
        REQUIRE_NOTHROW(normalFile.append("Hello"));
        REQUIRE(normalFile.pageCount() == 1);
    }

    SECTION("Append to read-only file throws") {
        REQUIRE_THROWS_AS(lockedFile.append("text"), UnauthorizedAccessException);
    }

    SECTION("Page count for large file") {
        normalFile.append(std::string(1200, 'x'));
        REQUIRE(normalFile.pageCount() == 3);
    }

    SECTION("Fit into folder space") {
        REQUIRE(normalFile.fitInto(20) == 10); 
        REQUIRE_THROWS_AS(normalFile.fitInto(5), DiskFullException);
    }
}