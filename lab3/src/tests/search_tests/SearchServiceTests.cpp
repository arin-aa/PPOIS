#include <catch2/catch_test_macros.hpp>
#include "SearchService.h"
#include "ContentCatalog.h"
#include "MediaLibrary.h"
#include "SearchQuery.h"
#include "SearchResult.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"

TEST_CASE("SearchService: Full Search") {
    Track t1(1, "Rock Song", 1, 1, 1000, nullptr);
    Album a1(1, "rock album", 1, {});
    Artist ar1(1, "rock artist", {}, "");
    
    MediaLibrary library({&t1}, {&a1}, {&ar1});
    ContentCatalog catalog(&library);
    catalog.rebuildIndex(); // Важно для поиска треков
    SearchService service(&catalog);

    SECTION("Empty query returns empty result") {
        SearchQuery q("   ");
        REQUIRE(service.search(q).getTotalCount() == 0);
    }

    SECTION("Search without type filter finds everything") {
        SearchQuery q("rock"); // typeFilter по умолчанию пустой
        SearchResult res = service.search(q);
        
        REQUIRE(res.getTotalCount() == 3);
        REQUIRE(res.getTopResult() == "Rock Song");
    }

    SECTION("Search with type filter only finds specific type") {
        SearchQuery albumQuery("rock", "album");
        SearchResult albumRes = service.search(albumQuery);
        
        REQUIRE(albumRes.getTotalCount() == 1);
        REQUIRE(albumRes.getTopResult() == "rock album");

        SearchQuery artistQuery("rock", "artist");
        SearchResult artistRes = service.search(artistQuery);
        
        REQUIRE(artistRes.getTotalCount() == 1);
        REQUIRE(artistRes.getTopResult() == "rock artist");
    }
}

TEST_CASE("SearchService: Suggestions") {
    // Создаем 6 треков, чтобы проверить ограничение в 5 штук
    Track t1(1, "Apple", 1, 1, 1000, nullptr);
    Track t2(2, "Apricot", 1, 1, 1000, nullptr);
    Track t3(3, "Avocado", 1, 1, 1000, nullptr);
    Track t4(4, "Almond", 1, 1, 1000, nullptr);
    Track t5(5, "Ant", 1, 1, 1000, nullptr);
    Track t6(6, "Banana", 1, 1, 1000, nullptr);
    
    MediaLibrary library({&t1, &t2, &t3, &t4, &t5, &t6});
    ContentCatalog catalog(&library);
    SearchService service(&catalog);

    SECTION("Empty prefix returns up to 5 tracks") {
        auto res = service.suggest("");
        REQUIRE(res.size() == 5); // MAX_SUGGESTIONS = 5
    }

    SECTION("Prefix 'A' returns matching tracks limited to 5") {
        auto res = service.suggest("A");
        REQUIRE(res.size() == 5);
    }

    SECTION("Prefix 'Ap' returns 2 specific tracks") {
        auto res = service.suggest("Ap");
        REQUIRE(res.size() == 2);
        REQUIRE(res[0] == "Apple");
        REQUIRE(res[1] == "Apricot");
    }

    SECTION("Prefix 'Z' returns empty vector") {
        auto res = service.suggest("Z");
        REQUIRE(res.empty() == true);
    }
    
    SECTION("Suggestion is case-sensitive (lowercase 'a' won't match 'Apple')") {
        auto res = service.suggest("a");
        REQUIRE(res.empty() == true); 
    }
}