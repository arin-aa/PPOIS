#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "TicTacToe.h"
#include <sstream>
#include <string>
#include <stdexcept>

TEST_CASE("Constructor", "[TicTacToe]") {
    TicTacToe game(3);
    REQUIRE(game.getSize() == 3);
    REQUIRE(game.getCurrentPlayer() == Cell::cross);
    REQUIRE(game.getWinner() == Cell::empty);
}

TEST_CASE("inRange", "[TicTacToe]") {
    TicTacToe game(3);
    REQUIRE(game.inRange(0, 0));
    REQUIRE(game.inRange(2, 2));
    REQUIRE_FALSE(game.inRange(-1, 0));
    REQUIRE_FALSE(game.inRange(3, 3));
}

TEST_CASE("makeMove", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0);
    REQUIRE(game[{0, 0}] == Cell::cross);
    REQUIRE(game.getCurrentPlayer() == Cell::nought);
    REQUIRE_THROWS_AS(game.makeMove(0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(game.makeMove(-1, 0), std::out_of_range);
}

TEST_CASE("Win by row", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0); game.makeMove(1, 0);
    game.makeMove(0, 1); game.makeMove(1, 1);
    game.makeMove(0, 2);
    REQUIRE(game.checkWin(Cell::cross));
    REQUIRE(game.isWon());
    REQUIRE(game.getWinner() == Cell::cross);
}

TEST_CASE("Win by column", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0); game.makeMove(0, 1);
    game.makeMove(1, 0); game.makeMove(1, 1);
    game.makeMove(2, 0);
    REQUIRE(game.checkWin(Cell::cross));
}

TEST_CASE("Win by diagonal", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0); game.makeMove(0, 1);
    game.makeMove(1, 1); game.makeMove(0, 2);
    game.makeMove(2, 2);
    REQUIRE(game.checkWin(Cell::cross));
}

TEST_CASE("Draw", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0); 
    game.makeMove(0, 1); 
    game.makeMove(0, 2); 
    game.makeMove(1, 1); 
    game.makeMove(1, 0); 
    game.makeMove(1, 2); 
    game.makeMove(2, 1); 
    game.makeMove(2, 0); 
    game.makeMove(2, 2); 
    REQUIRE(game.isDraw());
    REQUIRE_FALSE(game.isWon());
}

TEST_CASE("operator<< outputs board correctly", "[TicTacToe]") {
    TicTacToe game(3);
    game.makeMove(0, 0); 
    game.makeMove(1, 1); 

    std::ostringstream out;
    out << game;
    std::string result = out.str();

    REQUIRE(result.find('X') != std::string::npos);
    REQUIRE(result.find('O') != std::string::npos);
    REQUIRE(result.find('|') != std::string::npos);
    REQUIRE(result.find("--") != std::string::npos);
}

TEST_CASE("operator<< on 5x5 board", "[TicTacToe]") {
    TicTacToe game(5);
    std::ostringstream out;
    out << game;
    std::string result = out.str();

    REQUIRE(!result.empty());
}