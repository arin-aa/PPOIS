#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "User.h"

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

TEST_CASE("User: Default constructor") {
    REQUIRE_NOTHROW(User());
}