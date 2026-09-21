#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <iostream>
#include <utility>

enum class Cell: char{cross='X',nought='O',empty=' '};
class TicTacToe{
    private:
    int size;
    std::vector<std::vector<Cell>> board;
    Cell winner;
    Cell currentPlayer;

    public:
    TicTacToe(int newSize=3);
    const Cell& operator[](std::pair<int,int> position)const;
   
    bool inRange(int row,int column)const;
    void makeMove(int row,int column);
    
    bool checkWin(Cell player)const;
    bool isDraw()const;
    bool isWon()const;

    int getSize()const{
        return size;
    }
    Cell getCurrentPlayer()const{
        return currentPlayer;
    }
    Cell getWinner()const{
        return winner;
    }
    friend std::ostream& operator<<(std::ostream& output,const TicTacToe& game);
};
#endif