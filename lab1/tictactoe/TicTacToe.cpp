#include "TicTacToe.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

TicTacToe::TicTacToe(int newSize):size(newSize),board(newSize,vector<Cell>(newSize,Cell::empty)),winner(Cell::empty),currentPlayer(Cell::cross)
{}

const Cell& TicTacToe::operator[](pair<int,int> position)const{
    return board[position.first][position.second];
}

bool TicTacToe::inRange(int row,int column)const{
    return row>=0 && row<size && column>=0 && column<size;
}

bool TicTacToe::isWon()const{
    return winner!=Cell::empty;
}

bool TicTacToe::checkWin(Cell player)const{
    for(int i=0;i<size;i++){
        bool rowWin=true,colWin=true;
        for(int j=0;j<size;j++){
            if(board[i][j]!=player){
                rowWin=false;
            }
            if(board[j][i]!=player){
                colWin=false;
            }
        }
        if(rowWin||colWin){
            return true;
        }
    }

    bool diag1=true,diag2=true;
    for(int i=0;i<size;i++){
        if(board[i][i]!=player){
            diag1=false;
        }
        if(board[i][size-1-i]!=player){
            diag2=false;
        }
    }
    return diag1||diag2;
}

void TicTacToe::makeMove(int row,int column){
    if(winner!=Cell::empty){
        throw logic_error("Игра уже закончена.\n");
    }
    if(!inRange(row,column)){
        throw out_of_range("Координаты вне диапазона доски.\n");
    }
    if(board[row][column]!=Cell::empty){
        throw invalid_argument("Данная клетка уже занята. Попробуйте снова.\n");
    }
    board[row][column]=currentPlayer;
    if(checkWin(currentPlayer)){
        winner=currentPlayer;
    }
    else{
        currentPlayer=(currentPlayer==Cell::cross)?Cell::nought:Cell::cross;
    }
}

bool TicTacToe::isDraw()const{
    if(isWon()){
        return false;
    }
    for(int row=0;row<size;row++){
        for(int col=0;col<size;col++){
            if(board[row][col]==Cell::empty){
                return false;
            }
        }
    }
    return true;
}

ostream& operator<<(ostream& output,const TicTacToe& game_){
    for(int row=0;row<game_.size;row++){
        for(int col=0;col<game_.size;col++){
            output<<static_cast<char>(game_.board[row][col]);
            if(col<game_.size-1){
                output<<'|';
            } 
        }
        output<<'\n';
        if(row<game_.size-1){
            for(int col=0;col<game_.size;col++){
                output<<"--";
            }
        }
        output<<'\n';
    }
    return output;
}




