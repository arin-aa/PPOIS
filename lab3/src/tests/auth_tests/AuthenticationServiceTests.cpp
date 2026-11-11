#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "AuthenticationService.h"
#include "Subscription.h"
#include "User.h"
#include "MusicPlayerExceptions.h"
#include "User.h"

TEST_CASE("AuthenticationService: SignIn validation") {
    AuthenticationService auth;
    Subscription sub("Premium", 1000, true);
    User user("u1", "test@mail.com", "Tester", &sub);

    SECTION("Null user throws UserNotFoundException") {
        REQUIRE_THROWS_AS(auth.signIn(nullptr, "password1"), UserNotFoundException);
    }

    SECTION("Short password throws AuthenticationException") {
        REQUIRE_THROWS_AS(auth.signIn(&user, "abc"), AuthenticationException);
    }

    SECTION("Password without digit throws AuthenticationException") {
        REQUIRE_THROWS_AS(auth.signIn(&user, "abcdefgh"), AuthenticationException);
    }

    SECTION("Valid password signs the user in") {
        REQUIRE(auth.signIn(&user, "password1") == &user);
    }
}

TEST_CASE("AuthenticationService: Lockout and reset") {
    AuthenticationService auth;
    User user("u1", "test@mail.com", "Tester", nullptr);

    SECTION("Successful sign-in resets failed attempts") {
        for(int i=0; i<3; ++i) {
            REQUIRE_THROWS_AS(auth.signIn(&user, "bad"), AuthenticationException);
        }
        REQUIRE_NOTHROW(auth.signIn(&user, "valid123"));
        for(int i=0; i<3; ++i) {
            REQUIRE_THROWS_AS(auth.signIn(&user, "bad"), AuthenticationException);
        }
    }

    SECTION("5 failed attempts lead to lockout") {
        for(int i=0; i<5; ++i) {
            REQUIRE_THROWS_AS(auth.signIn(&user, "bad"), AuthenticationException);
        }
        REQUIRE_THROWS_AS(auth.signIn(&user, "valid123"), InvalidPasswordException);
    }
}