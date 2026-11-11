#include <catch2/catch_test_macros.hpp>
#include "Comment.h"

TEST_CASE("Comment: isReply logic") {
    SECTION("Target starts with prefix is a reply") {
        Comment reply(1, "author1", "comment:123", "Nice track!");
        REQUIRE(reply.isReply() == true);
    }

    SECTION("Target does not start with prefix is not a reply") {
        Comment topLevel(2, "author1", "track:456", "First comment");
        REQUIRE(topLevel.isReply() == false);
    }

    SECTION("Empty target is not a reply") {
        Comment emptyTarget(3, "author1", "", "Hello");
        REQUIRE(emptyTarget.isReply() == false);
    }
}