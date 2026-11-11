#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Player.h"
#include "MusicPlayerExceptions.h"
#include "AudioEngine.h"
#include "Queue.h"
#include "PlaybackState.h"
#include "PlaybackHistory.h"
#include "Track.h"
#include "AudioFile.h"

TEST_CASE("Player: Playback and Seeking") {
    AudioEngine engine;
    Queue queue;
    PlaybackState state;
    PlaybackHistory history("user");
    Player player(&engine, &queue, &state, &history);

    AudioFile file("a.mp3", "mp3", 320, 100);
    Track playable(1, "Song", 1, 1, 1000, &file);
    Track broken(2, "Broken", 1, 1, 1000, nullptr); // Нет файла

    SECTION("play throws if track is not playable") {
        queue.add(&broken);
        // Внутри play() вызовется startTrack(), который бросит исключение
        REQUIRE_THROWS_AS(player.play(), PlaybackException);
    }

    SECTION("play loads and plays valid track from queue") {
        queue.add(&playable);
        REQUIRE_NOTHROW(player.play());
        REQUIRE(state.getCurrentTrack() == &playable);
        
        // Повторный вызов play (трек уже загружен, плеер просто продолжит)
        REQUIRE_NOTHROW(player.play());
    }

    SECTION("seek throws without track or out of bounds") {
        // 1. Без трека
        REQUIRE_THROWS_AS(player.seek(100), PlaybackException);
        
        // 2. Загружаем трек через play() и проверяем границы
        queue.add(&playable);
        player.play();
        
        REQUIRE_THROWS_AS(player.seek(-1), PlaybackException);
        REQUIRE_THROWS_AS(player.seek(1500), PlaybackException);
        
        REQUIRE_NOTHROW(player.seek(500));
    }

    SECTION("pause and stop update state") {
        queue.add(&playable);
        player.play();
        
        REQUIRE_NOTHROW(player.pause());
        REQUIRE_NOTHROW(player.stop(1000));
    }

    SECTION("next and previous navigate queue and record session") {
        Track second(3, "Second", 1, 1, 1000, &file);
        queue.add(&playable);
        queue.add(&second);

        player.play(); // Загрузили первый трек
        state.updatePosition(500); // Эмулируем, что мы что-то послушали
        
        // Переключаем на следующий
        REQUIRE_NOTHROW(player.next(1000));
        REQUIRE(state.getCurrentTrack() == &second);
        REQUIRE(history.getSessions().size() == 1); // Сессия записалась

        // Возвращаемся назад
        REQUIRE_NOTHROW(player.previous(2000));
        REQUIRE(state.getCurrentTrack() == &playable);
    }
}