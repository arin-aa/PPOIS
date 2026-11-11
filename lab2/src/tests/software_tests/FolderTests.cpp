#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Folder.h"
#include "File.h"

TEST_CASE("Folder: Adding Files and Pages") {
    Folder folder(15); 
    File file1("a.txt", 5, false);
    File file2("b.txt", 20, false);

    SECTION("Add file that fits") {
        REQUIRE_NOTHROW(folder.addFile(&file1));
    }

    SECTION("Add file that does not fit throws") {
        REQUIRE_THROWS_AS(folder.addFile(&file2), DiskFullException);
    }

    SECTION("Total pages sums correctly") {
        file1.append(std::string(600, 'a')); 
        folder.addFile(&file1);
        REQUIRE(folder.totalPages() == 2);
    }
}