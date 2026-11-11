#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "TagEditor.h"
#include "MusicPlayerExceptions.h"
#include <map>

TEST_CASE("TagEditor: Reading tags") {
    TagEditor editor;

    SECTION("Read simple file without artist") {
        auto tags = editor.readTags("music/song.mp3");
        
        REQUIRE(tags["title"] == "song");
        REQUIRE(tags["format"] == "mp3");
        REQUIRE(tags.find("artist") == tags.end()); // Артиста нет
    }

    SECTION("Read file with artist separated by ' - '") {
        auto tags = editor.readTags("music/Queen - Bohemian Rhapsody.mp3");
        
        REQUIRE(tags["artist"] == "Queen");
        REQUIRE(tags["title"] == "Bohemian Rhapsody");
        REQUIRE(tags["format"] == "mp3");
    }

    SECTION("Read file in root directory (no path)") {
        auto tags = editor.readTags("track.flac");
        
        REQUIRE(tags["title"] == "track");
        REQUIRE(tags["format"] == "flac");
    }

    SECTION("Throw on unsupported format") {
        REQUIRE_THROWS_AS(editor.readTags("music/video.mp4"), MetadataException);
    }

    SECTION("Throw on missing extension") {
        REQUIRE_THROWS_AS(editor.readTags("music/no_extension"), MetadataException);
    }
}

TEST_CASE("TagEditor: Writing tags") {
    TagEditor editor;
    std::string originalUri = "music/old_name.mp3";

    SECTION("Write with artist and title") {
        std::map<std::string, std::string> tags = {
            {"title", "New Song"},
            {"artist", "New Artist"}
        };
        
        std::string newUri = editor.writeTags(originalUri, tags);
        // Ожидаем: music/New Artist - New Song.mp3
        REQUIRE(newUri == "music/New Artist - New Song.mp3");
    }

    SECTION("Write without artist") {
        std::map<std::string, std::string> tags = {
            {"title", "Solo Track"}
        };
        
        std::string newUri = editor.writeTags(originalUri, tags);
        // Ожидаем: music/Solo Track.mp3
        REQUIRE(newUri == "music/Solo Track.mp3");
    }

    SECTION("Throw if title is missing") {
        std::map<std::string, std::string> tags = {
            {"artist", "Only Artist"}
        };
        REQUIRE_THROWS_AS(editor.writeTags(originalUri, tags), MetadataException);
    }

    SECTION("Throw if title is empty") {
        std::map<std::string, std::string> tags = {
            {"title", ""}
        };
        REQUIRE_THROWS_AS(editor.writeTags(originalUri, tags), MetadataException);
    }

    SECTION("Throw on unsupported format during write") {
        std::map<std::string, std::string> tags = {
            {"title", "Valid Title"}
        };
        // Пытаемся записать теги в файл .txt
        REQUIRE_THROWS_AS(editor.writeTags("music/text.txt", tags), MetadataException);
    }
}