#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Inventory.h"
#include "Component.h"

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