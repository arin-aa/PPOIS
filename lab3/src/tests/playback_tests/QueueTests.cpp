#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Queue.h"
#include "MusicPlayerExceptions.h"
#include "Track.h"

TEST_CASE("Queue: Navigation and Modes") {
    Track t1(1, "A", 1, 1, 1000, nullptr);
    Track t2(2, "B", 1, 1, 1000, nullptr);
    Track t3(3, "C", 1, 1, 1000, nullptr);

    SECTION("Empty queue throws on getCurrent") {
        Queue q;
        REQUIRE_THROWS_AS(q.getCurrent(), PlaybackException);
    }

    SECTION("Standard navigation without repeat") {
        Queue q;
        q.add(&t1); q.add(&t2);
        
        REQUIRE(q.getCurrent() == &t1);
        REQUIRE(q.next() == &t2);
        
        // Конец очереди, повтор выключен
        REQUIRE_THROWS_AS(q.next(), PlaybackException); 
        
        // Возврат в начало
        REQUIRE(q.previous() == &t1);
        REQUIRE(q.previous() == &t1); // Уже в начале, не падает, остается на t1
    }

    SECTION("Repeat One stays on the same track") {
        Queue q("one");
        q.add(&t1); q.add(&t2);
        REQUIRE(q.next() == &t1);
        REQUIRE(q.previous() == &t1);
    }

    SECTION("Repeat All wraps around") {
        Queue q("all");
        q.add(&t1); q.add(&t2);
        
        q.next(); // Теперь на t2
        REQUIRE(q.next() == &t1); // Завернулись в начало
        
        REQUIRE(q.previous() == &t2); // Завернулись в конец
    }
}