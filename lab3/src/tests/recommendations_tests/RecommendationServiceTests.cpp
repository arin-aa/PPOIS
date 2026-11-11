#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "RecommendationService.h"
#include "MediaLibrary.h"
#include "MusicPlayerExceptions.h"
#include "PlaybackHistory.h"
#include "PlaybackSession.h"
#include "Track.h"

TEST_CASE("RecommendationService: Recommend For") {
    // Настраиваем треки: 
    // t1 - Rock (id 1), t2 - Pop (id 2), t3 - Rock/Pop (id 1, 2)
    Track t1(1, "Rock Song", 1, 1, 1000, nullptr, {1});
    Track t2(2, "Pop Song", 1, 1, 1000, nullptr, {2});
    Track t3(3, "Rock-Pop Song", 1, 1, 1000, nullptr, {1, 2});
    
    MediaLibrary library({&t1, &t2, &t3});
    PlaybackHistory history("user1");
    RecommendationService recommender(&history, &library);

    SECTION("Empty history returns empty recommendations") {
        REQUIRE(recommender.recommendFor(5).empty());
    }

    SECTION("Recommends tracks matching listened genres") {
        // Пользователь слушал t1 (Rock)
        PlaybackSession session(&t1, 0);
        history.add(session);

        auto result = recommender.recommendFor(10);
        
        // Должен найти t1 (Rock) и t3 (Rock/Pop). t2 (Pop) не подходит.
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == &t1);
        REQUIRE(result[1] == &t3);
    }

    SECTION("Respects the limit count") {
        PlaybackSession session(&t1, 0);
        history.add(session);

        // Просим только 1 рекомендацию
        auto result = recommender.recommendFor(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == &t1);
    }

    SECTION("Returns empty if no tracks share genres with history") {
        Track jazz(4, "Jazz Song", 1, 1, 1000, nullptr, {3});
        PlaybackSession session(&jazz, 0);
        history.add(session); // Слушали только джаз

        // В библиотеке нет джаза
        REQUIRE(recommender.recommendFor(5).empty());
    }
}

TEST_CASE("RecommendationService: Similar Tracks") {
    Track t1(1, "Rock Song", 1, 1, 1000, nullptr, {1}); // Reference track
    Track t2(2, "Pop Song", 1, 1, 1000, nullptr, {2});
    Track t3(3, "Rock-Pop Song", 1, 1, 1000, nullptr, {1, 2});
    Track t4(4, "Rock Ballad", 1, 1, 1000, nullptr, {1});
    
    MediaLibrary library({&t1, &t2, &t3, &t4});
    PlaybackHistory history("user1");
    RecommendationService recommender(&history, &library);

    SECTION("Throws if reference track is not found") {
        REQUIRE_THROWS_AS(recommender.similarTracks(99, 5), TrackNotFoundException);
    }

    SECTION("Finds tracks sharing genres, excluding the reference") {
        auto result = recommender.similarTracks(1, 10);
        
        // t1 (сам себя) исключается. 
        // t3 (Rock/Pop) и t4 (Rock) подходят. t2 (Pop) - нет.
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == &t3);
        REQUIRE(result[1] == &t4);
    }

    SECTION("Respects the limit count") {
        auto result = recommender.similarTracks(1, 1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == &t3);
    }

    SECTION("Returns empty if no candidates share genres") {
        auto result = recommender.similarTracks(2, 5); // Reference is t2 (Pop)
        // t3 (Rock/Pop) подходит, но если мы сделаем трек только с джазом:
        
        Track t5(5, "Jazz", 1, 1, 1000, nullptr, {3});
        MediaLibrary lib2({&t5, &t2});
        RecommendationService rec2(&history, &lib2);
        
        REQUIRE(rec2.similarTracks(2, 5).empty());
    }
}