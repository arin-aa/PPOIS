#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"
#include "PowerConnector.h"

TEST_CASE("PowerConnector: Attach") {
    PowerConnector conn(24);
    REQUIRE(conn.attach() == 24);
    REQUIRE_THROWS_AS(conn.attach(), InvalidConfigurationException);
}